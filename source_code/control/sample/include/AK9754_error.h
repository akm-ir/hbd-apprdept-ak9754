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

#ifndef INCLUDE_AK9754_ERROR_H
#define INCLUDE_AK9754_ERROR_H

/**
 * @enum error code in handling AK9754 and algorithm
 */
enum {
    CONTROL_SUCCESS = 0,
    AK9754_I2C_ERROR,                       /* i2c communication failed */
    AK9754_DEVICE_ERROR,                    /* invalid device detected */
    NULL_POINTER_ERROR,                     /* NULL handler, NULL data */
};

#endif  /* !defined(INCLUDE_AK9754_ERROR_H) */
