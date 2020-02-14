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

#ifndef INCLUDE_AK9754_CONTROL_H
#define INCLUDE_AK9754_CONTROL_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* defined(__cplusplus) */

extern int32_t AK9754_InitDevice(void);
extern int32_t AK9754_StartMeasure(void);
extern int32_t AK9754_StopMeasure(void);
extern int32_t AK9754_CheckInterrupt(uint8_t *is_detected, uint8_t *is_data_ready);
extern int32_t AK9754_ReadBlk(uint8_t *blk_data);
extern int32_t AK9754_ReadSb(uint8_t *sb_blk);
extern int32_t AK9754_PrepareAppDetec(void);
extern int32_t AK9754_PrepareDepartDetec(void);

#ifdef __cplusplus
}   /* extern "C" */
#endif  /* defined(__cplusplus) */

#endif  /* !defined(INCLUDE_AK9754_CONTROL_H) */
