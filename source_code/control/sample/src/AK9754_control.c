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
 *****************************************************************************/
/* Software version 1910-001_V01-BL02-00 */

#include "AK9754_control.h"
#include "AK9754_device.h"
#include "AK9754_error.h"
#include "AK9754_param.h"
#include "AKSIR.h"
#include "drivers.h"


/**
* @brief initialize AK9754 (enabled streaming buffer and internal algorithm)
* @return error code of i2c communication
* @retval CONTROL_SUCCESS on success
* @retval AK9754_I2C_ERROR on i2c communication error
* @retval AK9754_DEVICE_ERROR on BIST error
*/
int32_t AK9754_InitDevice(void)
{
    int32_t ret;
    uint8_t reg_val;

    /* software reset */
    ret = I2C_Write(AK9754_SLAVE_ADR, AK9754_CTRL1_REG, AK9754_CTRL1_SRST);
    if (ret != I2C_SUCCESS) {
        return AK9754_I2C_ERROR;
    }

    /* confirm company ID in the device */
    ret = I2C_Read(AK9754_SLAVE_ADR, AK9754_WIA1_REG, 1, &reg_val);
    if (ret != I2C_SUCCESS) {
        return AK9754_I2C_ERROR;
    }
    if (reg_val != AK9754_COMPANY_ID) {
        return AK9754_DEVICE_ERROR;
    }

    /* confirm device ID */
    ret = I2C_Read(AK9754_SLAVE_ADR, AK9754_WIA2_REG, 1, &reg_val);
    if (ret != I2C_SUCCESS) {
        return AK9754_I2C_ERROR;
    }
    if (reg_val != AK9754_DEVICE_ID) {
        return AK9754_DEVICE_ERROR;
    }

    /*
     * setup measurement conditions (CTRL3 ~ CTRL6)
     */
    /* CTRL3 : lownoise mode / odr:10Hz / fctmp / fcir settings */
    ret = I2C_Write(AK9754_SLAVE_ADR, AK9754_CTRL3_REG,
                    AK9754_CTRL3(AK9754_LNM_VAL, AK9754_ODR_VAL_APP,
                                 AK9754_FCTMP_VAL_DEFAULT,
                                 AK9754_FCIR_VAL_DEFAULT));
    if (ret != I2C_SUCCESS) {
        return AK9754_I2C_ERROR;
    }

    /* CTRL4 : TOPT mode settings */
    ret = I2C_Write(AK9754_SLAVE_ADR, AK9754_CTRL4_REG, AK9754_TOPT_VAL);
    if (ret != I2C_SUCCESS) {
        return AK9754_I2C_ERROR;
    }

    /* CTRL5 : TMP offset settings */
    /* Showing how to set register value. Hardware default value is set. */
    ret = I2C_Write(AK9754_SLAVE_ADR, AK9754_CTRL5_REG,
                    AK9754_TMPOFS_VAL_DEFAULT);
    if (ret != I2C_SUCCESS) {
        return AK9754_I2C_ERROR;
    }

    /* CTRL6 : IR signal gain settings */
    /* Showing how to set register value. Hardware default value is set. */
    ret = I2C_Write(AK9754_SLAVE_ADR, AK9754_CTRL6_REG,
                    AK9754_IRGAIN_VAL_DEFAULT);
    if (ret != I2C_SUCCESS) {
        return AK9754_I2C_ERROR;
    }

    /*
     * setup parameteres for human body detection (CTRL7 ~ CTRL10)
     */
    /* CTRL7 : invert mode /  settings */
    /* Showing how to set register value. Hardware default value is set. */
    ret = I2C_Write(AK9754_SLAVE_ADR, AK9754_CTRL7_REG,
                    AK9754_CTRL7(AK9754_IRINV_VAL_DEFAULT,
                                 AK9754_IDLET_VAL_DEFAULT));
    if (ret != I2C_SUCCESS) {
        return AK9754_I2C_ERROR;
    }

    /* CTRL8 : NSAMPLE settings */
    /* Showing how to set register value. Hardware default value is set. */
    ret = I2C_Write(AK9754_SLAVE_ADR, AK9754_CTRL8_REG, AK9754_DTCT_VAL_DEFAULT);
    if (ret != I2C_SUCCESS) {
        return AK9754_I2C_ERROR;
    }

    /* CTRL9 : threshold level settings (lower) */
    ret = I2C_Write(AK9754_SLAVE_ADR, AK9754_CTRL9_REG,
                    AK9754_CTRL9(AK9754_HBDTH_VAL));
    if (ret != I2C_SUCCESS) {
        return AK9754_I2C_ERROR;
    }

    /* CTRL10 : threshold level settings (upper) */
    ret = I2C_Write(AK9754_SLAVE_ADR, AK9754_CTRL10_REG,
                    AK9754_CTRL10(AK9754_HBDTH_VAL));
    if (ret != I2C_SUCCESS) {
        return AK9754_I2C_ERROR;
    }

    /*
     * device interrupt settings
     * in this configuration, AK9754 rise interrupts when human is detected
     */
    /* CTRL11 : function's enable / disable settings */
    ret = I2C_Write(AK9754_SLAVE_ADR, AK9754_CTRL11_REG,
                    AK9754_CNTL11_HBDEN | AK9754_CNTL11_SBHBD |
                    AK9754_CNTL11_SBEN | AK9754_CNTL11_HBDIEN);
    if (ret != I2C_SUCCESS) {
        return AK9754_I2C_ERROR;
    }

    return CONTROL_SUCCESS;
}

/**
* @brief start measurement by AK9754
* @return error code of i2c communication
* @retval CONTROL_SUCCESS on success
* @retval AK9754_I2C_ERROR on i2c communication error
*/
int32_t AK9754_StartMeasure(void)
{
    int32_t ret;
    ret = I2C_Write(AK9754_SLAVE_ADR, AK9754_CTRL12_REG,
                    AK9754_CTRL12_MODE_MEASURE);

    if (ret != I2C_SUCCESS) {
        return AK9754_I2C_ERROR;
    }
    return CONTROL_SUCCESS;
}

/**
* @brief stop measurement by AK9754
* @return error code of i2c communication
* @retval CONTROL_SUCCESS on success
* @retval AK9754_I2C_ERROR on i2c communication error
*/
int32_t AK9754_StopMeasure(void)
{
    int32_t ret;
    ret = I2C_Write(AK9754_SLAVE_ADR, AK9754_CTRL12_REG,
                    AK9754_CTRL12_MODE_STANDBY);

    if (ret != I2C_SUCCESS) {
        return AK9754_I2C_ERROR;
    }
    return CONTROL_SUCCESS;
}

/**
* @brief check interrupt source of AK9754
* @param[in,out]  is_detected    flag either if human is detected or not
* @param[in,out]  is_data_ready  flag either if data is ready or not
* @return error code of i2c communication
* @retval CONTROL_SUCCESS on success
* @retval AK9754_I2C_ERROR on i2c communication error
*/
int32_t AK9754_CheckInterrupt(uint8_t *is_detected, uint8_t *is_data_ready)
{
    int32_t ret;
    uint8_t reg_val;

    ret = I2C_Read(AK9754_SLAVE_ADR, AK9754_ST1_REG, 1, &reg_val);
    if (ret != I2C_SUCCESS) {
        return AK9754_I2C_ERROR;
    }
    /* check HBD register's value */
    *is_detected = ((reg_val & AK9754_ST1_HBDR1) == 0) ? FALSE : TRUE;

    /* check data-ready register's value */
    *is_data_ready = ((reg_val & AK9754_ST1_DRDY) == 0) ? FALSE : TRUE;

    return CONTROL_SUCCESS;
}


/**
* @brief get measurement data from AK9754
* @param[out]  blk_data    measurement data of AK9754
* @return error code of i2c communication
* @retval CONTROL_SUCCESS on success
* @retval AK9754_I2C_ERROR on i2c communication error
*/
int32_t AK9754_ReadBlk(uint8_t *blk_data)
{
    int32_t ret;

    ret = I2C_Read(AK9754_SLAVE_ADR, AK9754_ST1_REG,
                   NUM_OF_BYTES_IR_BLK, blk_data);
    if (ret != I2C_SUCCESS) {
        return AK9754_I2C_ERROR;
    }

    return CONTROL_SUCCESS;
}

/**
* @brief get measurement data in streaming buffer
* @param[out]  sb_blk    measuremant data in streaming buffer
* @return error code of i2c communication
* @retval CONTROL_SUCCESS on success
* @retval AK9754_I2C_ERROR on i2c communication error
*/
int32_t AK9754_ReadSb(uint8_t *sb_blk)
{
    int32_t ret;

    ret = I2C_Read(AK9754_SLAVE_ADR, AK9754_ST3_REG,
                   NUM_OF_BYTES_STREAMING_BUF_BLK, sb_blk);
    if (ret != I2C_SUCCESS) {
        return AK9754_I2C_ERROR;
    }

    return CONTROL_SUCCESS;
}

/**
* @brief change AK9754 interrupt setting to detect human approach
*        (enable interrupt on human approach detection)
* @return error code of i2c communication
* @retval CONTROL_SUCCESS on success
* @retval AK9754_I2C_ERROR on i2c communication error
*/
int32_t AK9754_PrepareAppDetec(void)
{
    int32_t ret;

    /* CTRL3 : lownoise mode / odr:10Hz / fctmp / fcir settings */
    ret = I2C_Write(AK9754_SLAVE_ADR, AK9754_CTRL3_REG,
                    AK9754_CTRL3(AK9754_LNM_VAL, AK9754_ODR_VAL_APP,
                                 AK9754_FCTMP_VAL_DEFAULT,
                                 AK9754_FCIR_VAL_DEFAULT));
    if (ret != I2C_SUCCESS) {
        return AK9754_I2C_ERROR;
    }

    /* CTRL9 : threshold level settings (lower) */
    ret = I2C_Write(AK9754_SLAVE_ADR, AK9754_CTRL9_REG,
                    AK9754_CTRL9(AK9754_HBDTH_VAL));
    if (ret != I2C_SUCCESS) {
        return AK9754_I2C_ERROR;
    }

    /* CTRL10 : threshold level settings (upper) */
    ret = I2C_Write(AK9754_SLAVE_ADR, AK9754_CTRL10_REG,
                    AK9754_CTRL10(AK9754_HBDTH_VAL));
    if (ret != I2C_SUCCESS) {
        return AK9754_I2C_ERROR;
    }

    /*
    * device interrupt settings
    * in this configuration, AK9754 rise interrupts when human is detected
    */
    /* CTRL11 : function's enable / disable settings */
    ret = I2C_Write(AK9754_SLAVE_ADR, AK9754_CTRL11_REG,
                    AK9754_CNTL11_HBDEN | AK9754_CNTL11_SBHBD |
                    AK9754_CNTL11_SBEN | AK9754_CNTL11_HBDIEN);
    if (ret != I2C_SUCCESS) {
        return AK9754_I2C_ERROR;
    }

    return CONTROL_SUCCESS;
}


/**
* @brief change AK9754 interrupt setting to detect human departure
*        (enable interrupt on data ready)
* @return error code of i2c communication
* @retval CONTROL_SUCCESS on success
* @retval AK9754_I2C_ERROR on i2c communication error
*/
int32_t AK9754_PrepareDepartDetec(void)
{
    int32_t ret;

    /* CTRL3 : lownoise mode / odr:2Hz / fctmp / fcir settings */
    ret = I2C_Write(AK9754_SLAVE_ADR, AK9754_CTRL3_REG,
                    AK9754_CTRL3(AK9754_LNM_VAL, AK9754_ODR_VAL_DEP,
                                 AK9754_FCTMP_VAL_DEFAULT,
                                 AK9754_FCIR_VAL_DEFAULT));
    if (ret != I2C_SUCCESS) {
        return AK9754_I2C_ERROR;
    }

    /*
    * device interrupt settings
    *   in this configuration, AK9754 rise interrupts when data is ready
    */
    /* CTRL11 : function's enable / disable settings */
    ret = I2C_Write(AK9754_SLAVE_ADR, AK9754_CTRL11_REG,
                    AK9754_CNTL11_DRIEN);
    if (ret != I2C_SUCCESS) {
        return AK9754_I2C_ERROR;
    }

    return CONTROL_SUCCESS;
}