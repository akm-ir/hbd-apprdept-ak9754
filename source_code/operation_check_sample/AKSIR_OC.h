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

#ifndef INCLUDE_AKSIR_OC_H
#define INCLUDE_AKSIR_OC_H

#include "AKSIR.h"

#ifdef __cplusplus
extern "C" {
#endif /* defined(__cplusplus) */

extern int32_t AKSIR_CalcOc(AKSIR_HANDLE handle, const uint8_t *blk_data);

#ifdef __cplusplus
}   /* extern "C" */
#endif /* defined(__cplusplus) */

#endif /* !defined(INCLUDE_AKSIR_OC_H) */
