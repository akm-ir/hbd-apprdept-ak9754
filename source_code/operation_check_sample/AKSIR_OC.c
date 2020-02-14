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

#include "AKSIR_OC.h"

/**
 * @brief run algorithm with dummy sensor data
 * @param[in] handle    instance handle of algorithm
 * @param[in] blk_data  pointer to array of sensor data (not used)
 * @return result of algorithm
 * @retval AKSIR_ST_PRESENT   if human is present
 * @retval AKSIR_ST_DEPARTURE on human left (absence is detected)
 * @retval AKSIR_ST_ERROR     on error
 */
int32_t AKSIR_CalcOc(AKSIR_HANDLE handle, const uint8_t *blk_data)
{
    struct HBD      *hbd;
    int16_t         dummy_data[5] = {1000, 900, 800, -100, -200};
    int16_t         dummy_ir;
    int32_t         dummy_ir32;
    int32_t         state;
    uint8_t         dummy_blk[2];
    static uint32_t i = 0;

    if (((handle == NULL) || (blk_data == NULL))) {
        return AKSIR_ST_ERROR;
    }

    hbd = (struct HBD *)handle;

    dummy_ir32 = (int32_t)(hbd->depart_threshold + dummy_data[i]);
    if (dummy_ir32 > INT16_MAX) {
        dummy_ir32 = (int32_t)INT16_MAX;
    }
    if (dummy_ir32 < INT16_MIN) {
        dummy_ir32 = (int32_t)INT16_MIN;
    }

    dummy_ir = (int16_t)dummy_ir32;

    dummy_blk[0] = (uint8_t)(0x00ff & dummy_ir);
    dummy_blk[1] = (uint8_t)((0xff00 & dummy_ir) >> 8);

    state = AKSIR_Calc(handle, dummy_blk);
    if ((state == AKSIR_ST_PRESENT) && (i <= 3)) {
        i++;
    } else if ((state == AKSIR_ST_DEPARTURE) || (state == AKSIR_ST_ERROR)) {
        i = 0;
    } else {
        /* nothing to do */
    }

    return state;
}
