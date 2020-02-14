/******************************************************************************
*
* Copyright (C) 2019 Asahi Kasei Microdevices Corporation, Japan
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
******************************************************************************/
/* Software version 1910-001_V01-BL02-00 */

#include <stdint.h>

#include "AK9754_control.h"
#include "AK9754_device.h"
#include "AK9754_error.h"
#include "AK9754_param.h"
#include "AKSIR.h"
#include "drivers.h"

#ifndef AK9754_SLAVE_ADR
#error AK9754_SLAVE_ADR is not defined
#endif /* !defined(AK9754_SLAVE_ADR) */

/* size of work space for algorithm */
#define AKSIR_BUFF_SIZE_IN_BYTE    30

AKSIR_HANDLE      g_aksir_handle;
struct AKSIR_ATTR g_aksir_attr;
int8_t            g_aksir_buffer[AKSIR_BUFF_SIZE_IN_BYTE];

/**
* @brief initialize device and start measurement
*/
static int32_t StartProcess(void)
{
    int32_t ret;

    ret = AK9754_InitDevice();
    if (ret != CONTROL_SUCCESS) {
        return ret;
    }

    ret = AK9754_StartMeasure();
    if (ret != CONTROL_SUCCESS) {
        return ret;
    }

    return CONTROL_SUCCESS;
}

/**
* @brief initialize algorithm when approach is detected
*/
static int32_t PrepareDepartDetection(void)
{
    int32_t ret;
    uint8_t sb_valid;
    uint8_t sb_blk[NUM_OF_BYTES_STREAMING_BUF_BLK];

    ret = AK9754_StopMeasure();
    if (ret != CONTROL_SUCCESS) {
        return ret;
    }

    ret = AK9754_ReadSb(sb_blk);
    if (ret != CONTROL_SUCCESS) {
        return ret;
    }

    /* get valid number of IR data in streaming buffer */
    sb_valid = sb_blk[0] & (uint8_t)AK9754_ST3_SBNMB;

    /* feed sliced sb_blk data (from SB0L to SB9H) to AKSIR_Create() */
    g_aksir_handle = AKSIR_Create(&g_aksir_attr, g_aksir_buffer,
                                  sizeof(g_aksir_buffer),
                                  &sb_blk[AK9754_SB0L_REG - AK9754_ST3_REG],
                                  sb_valid);
    if (g_aksir_handle == NULL) {
        return NULL_POINTER_ERROR;
    }

    ret = AK9754_PrepareDepartDetec();
    if (ret != CONTROL_SUCCESS) {
        return ret;
    }

    ret = AK9754_StartMeasure();
    if (ret != CONTROL_SUCCESS) {
        return ret;
    }

    return CONTROL_SUCCESS;
}

/**
* @brief do action according to state. start approach detection when departure is detected
*/
static int32_t ProcessState(int32_t state)
{
    int32_t ret;

    switch (state) {
    case AKSIR_ST_DEPARTURE:
        /*******************************************************************
        * here, please trigger your process by human departure detection
        ********************************************************************/

        ret = AK9754_StopMeasure();
        if (ret != CONTROL_SUCCESS) {
            return ret;
        }

        ret = AK9754_PrepareAppDetec();
        if (ret != CONTROL_SUCCESS) {
            return ret;
        }

        ret = AK9754_StartMeasure();
        if (ret != CONTROL_SUCCESS) {
            return ret;
        }

        break;
    case AKSIR_ST_PRESENT:
        /* not detected, continue detecting */
        /* nothing to do */
        break;
    case AKSIR_ST_ERROR:
        /* error */
        return NULL_POINTER_ERROR;
    default:
        /* not reached */
        break;
    }

    return CONTROL_SUCCESS;
}


/**
* @brief sample flow of device control and algorithm
*/
int32_t main(void)
{
    int32_t ret;
    int32_t state;
    uint8_t is_detected = 0;
    uint8_t is_data_ready = 0;
    uint8_t blk_data[NUM_OF_BYTES_IR_BLK];

    g_aksir_attr.num_of_depart_counts = NUMBER_OF_DEPARTURE_COUNTS;
    g_aksir_attr.min_delta = MIN_DELTA;

    /*
     * wait for AK9754 to be ready to use
     * wait time = PSUPmax + PORT = 50ms + 100us < 51ms (worst case)
     */
    WaitMsec(AK9754_PSUP_PORT_IN_MSEC); /* just as example. a timer interrupt can also be used */

    ret = StartProcess();
    if (ret != CONTROL_SUCCESS) {
        /* when AK9754_I2C_ERROR is returned,
        * please check the part related to
        * i2c communication. (wire connection, slave address, ...)
        *
        * when AK9754_DEVICE_ERROR is returned,
        * please check if the connected device is AK9754
        */
        return ret;
    }


    for (;;) {
        /*
         * just as an example,
         * set the mcu to sleep and wait for interrupt
         */
        McuSleep();
        /* interrupt occured, mcu awaken */
        ret = AK9754_CheckInterrupt(&is_detected, &is_data_ready);
        if (ret != CONTROL_SUCCESS) {
            return ret;
        }
        /* read blk data (ST1, IRL, IRH, TMPL, TMPH, ST2) and reset INTN */
        ret = AK9754_ReadBlk(blk_data);
        if (ret != CONTROL_SUCCESS) {
            return ret;
        }

        if (is_detected == TRUE) {
            /* this block is excecuted when approach is detected in absent state */

            /******************************************************************
            * here, please trigger your process by human approach detection
            ******************************************************************/

            ret = PrepareDepartDetection();
            if (ret != CONTROL_SUCCESS) {
                return ret;
            }
        } else if (is_data_ready == TRUE) {
            /* this block is excecuted when data is ready in present state */

            /* feed sliced blk_data data (from IR1L to TMPH) to AKSIR_Calc() */
            state = AKSIR_Calc(g_aksir_handle,
                               &blk_data[AK9754_IRDL_REG - AK9754_ST1_REG]);

            ret = ProcessState(state);
            if (ret != CONTROL_SUCCESS) {
                return ret;
            }
        } else {
            /* nothing to do */
        }
    }
}
