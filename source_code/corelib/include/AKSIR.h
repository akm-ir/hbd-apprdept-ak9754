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

#ifndef INCLUDE_AKSIR_H
#define INCLUDE_AKSIR_H

#include <stdint.h>

#ifndef TRUE
#define TRUE 1
#endif /* !defined(TRUE) */

#ifndef FALSE
#define FALSE 0
#endif /* !defined(FALSE) */

#ifndef NULL
#define NULL    ((void *)0)
#endif /* !defined(NULL) */

#define COMPOSE_I16(b1, b2) (((int16_t)(b1) << 8) | (b2))

/* valid range of number of values in the streaming buffer */
#define MAX_NUMBER_OF_STREAMING_BUFFER 10
#define MIN_NUMBER_OF_STREAMING_BUFFER 2

typedef void *AKSIR_HANDLE;

/**
 * @enum HBD state
 * @brief state of detection
 */
enum {
    AKSIR_ST_ERROR = 0,
    AKSIR_ST_PRESENT,
    AKSIR_ST_DEPARTURE
};

/* struct of algorithm attributes */
struct AKSIR_ATTR {
    uint16_t num_of_depart_counts;
    uint16_t min_delta;
};

/* generic variables for Human Body Detection */
struct HBD {
    int16_t  depart_threshold;
    uint16_t min_delta;
    uint16_t num_of_depart_counts;
    uint16_t ntimes_below;
};

#ifdef __cplusplus
extern "C" {
#endif /* defined(__cplusplus) */

extern AKSIR_HANDLE AKSIR_Create(const struct AKSIR_ATTR *attr, void *buf,
                                 int32_t buf_size, const uint8_t *sb_blk,
                                 uint8_t sb_valid);
extern int32_t AKSIR_Calc(AKSIR_HANDLE handle, const uint8_t *blk_data);


#ifdef __cplusplus
}   /* extern "C" */
#endif  /* defined(__cplusplus) */

#endif /* !defined(INCLUDE_AKSIR_H) */
