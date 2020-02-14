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

#include "AKSIR.h"

/**
* @brief calculate departure threshold
*/
static int16_t CalcDepThres(struct HBD *hbd, const int16_t *sb, uint8_t sb_valid)
{
    int32_t ir_total;
    int32_t delta_calc;
    int32_t curr_delta;
    int16_t curr_hbd_level;
    int16_t curr_baseline;
    uint8_t ir_avg_num;
    uint8_t i;

    curr_hbd_level = sb[0];
    ir_total = 0;
    /* sb_valid has already been confirmed to be 2 or larger */
    ir_avg_num = sb_valid - 1;

    for (i = 1; i < sb_valid; i++) {
        ir_total = ir_total + (int32_t)sb[i];
    }

    curr_baseline = (int16_t)(ir_total / (int32_t)ir_avg_num);

    delta_calc = curr_hbd_level - curr_baseline;
    curr_delta = (delta_calc < (int32_t)(hbd->min_delta))
        ? (int32_t)(hbd->min_delta) : delta_calc;

    return curr_baseline + (int16_t)(curr_delta / 2);
}

/**
 * @brief calculate required buffer size
 *
 * NOTE: the buffer size is constant in current implementation.
 */
static int32_t BufSize(void)
{
    return (int32_t)(sizeof(struct HBD));
}

/**
 * @brief validate given attributes
 */
static int32_t IsValidAttr(const struct AKSIR_ATTR *attr)
{
    if (attr == NULL) {
        return FALSE;
    }

    if (attr->num_of_depart_counts == 0) {
        return FALSE;
    }

    return TRUE;
}

/**
 * @brief create new instance of algorithm
 * @param[in]      attr      pointer to struct of attributes
 * @param[in,out]  buf       pointer of work buffer
 * @param[in]      buf_size  size of work buffer
 * @param[in]      sb_blk    pointer to array of streaming buffer data
 * @param[in]      sb_valid  number of valid data in streaming buffer
 * @return instance handle of algorithm
 * @retval NULL on error
 */
AKSIR_HANDLE AKSIR_Create(const struct AKSIR_ATTR *attr, void *buf,
                          int32_t buf_size, const uint8_t *sb_blk,
                          uint8_t sb_valid)
{
    struct HBD *hbd;
    int16_t    sb_value[MAX_NUMBER_OF_STREAMING_BUFFER];
    uint8_t    i;

    if ((IsValidAttr(attr) == FALSE) ||
        (buf == NULL) ||
        (sb_blk == NULL) ||
        (buf_size < BufSize()) ||
        (sb_valid > MAX_NUMBER_OF_STREAMING_BUFFER) ||
        (sb_valid < MIN_NUMBER_OF_STREAMING_BUFFER)
    ) {
        return (AKSIR_HANDLE)NULL;
    }

    hbd = (struct HBD *)buf;

    hbd->min_delta = attr->min_delta;
    hbd->num_of_depart_counts = attr->num_of_depart_counts;
    hbd->ntimes_below = 0;

    for (i = 0; i < sb_valid; i++) {
        sb_value[i] = COMPOSE_I16(sb_blk[2 * i + 1], sb_blk[2 * i]);
    }

    hbd->depart_threshold = CalcDepThres(hbd, sb_value, sb_valid);

    return (AKSIR_HANDLE)hbd;
}

/**
 * @brief run algorithm with obtained sensor data
 * @param[in] handle    instance handle of algorithm
 * @param[in] blk_data  pointer to array of sensor data
 * @return result of algorithm
 * @retval AKSIR_ST_PRESENT   if human is present
 * @retval AKSIR_ST_DEPARTURE on human left (absence is detected)
 * @retval AKSIR_ST_ERROR     on error
 */
int32_t AKSIR_Calc(AKSIR_HANDLE handle, const uint8_t *blk_data)
{
    struct HBD *hbd;
    int16_t    ir;

    if (((handle == NULL) || (blk_data == NULL))) {
        return AKSIR_ST_ERROR;
    }

    hbd = (struct HBD *)handle;
    ir = COMPOSE_I16(blk_data[1], blk_data[0]);

    if (ir > hbd->depart_threshold) {
        /* present */
        hbd->ntimes_below = 0;
    } else {
        /* departing */
        hbd->ntimes_below++;
        if (hbd->ntimes_below >= hbd->num_of_depart_counts) {
            /* detected departure */
            return AKSIR_ST_DEPARTURE;
        }
    }
    /* not detected departure */
    return AKSIR_ST_PRESENT;
}
