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
            * for example, blink LED
            ******************************************************************/
        }
    }
}
