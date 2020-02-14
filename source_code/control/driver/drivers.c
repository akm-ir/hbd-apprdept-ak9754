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

#include "drivers.h"


/**
 * @brief Write one byte data to the command register of the device I2C address
 * @param slave_addr Device I2C slave address.
 * @param w_cmd      Command register of the write command
 * @param cmd_data   One byte data to write to the device
 * @return result of the function
 * @retval I2C_SUCCESS on success
 * @retval I2C_ERROR on error
 */
int32_t I2C_Write(uint8_t slave_addr, uint8_t w_cmd, uint8_t cmd_data)
{
    /* dummy implementation */
    return I2C_SUCCESS;
}

/**
  * @brief Read data from the command register of the device I2C address into the data buffer
  * @param slave_addr Device I2C slave address.
  * @param r_cmd      Command register of the read command
  * @param num_data   Number of data bytes to read to the device
  * @param p_buf      Pointer to the data buffer to read onto
  * @return result of the function
  * @retval I2C_SUCCESS on success
  * @retval I2C_ERROR on error
  */
int32_t I2C_Read(uint8_t slave_addr, uint8_t r_cmd, uint8_t num_data,
                 uint8_t *pbuf)
{
    /* dummy implementation */
    return I2C_SUCCESS;
}

/**
  * @brief Wait specified msec
  * @param  msec msec to wait
  * @return None
  */
void WaitMsec(int32_t msec)
{
    /* dummy implementation */
}

/**
  * @brief Make MCU entering to sleep
  * @return None
  */
void McuSleep(void)
{
    /* dummy implementation */
}
