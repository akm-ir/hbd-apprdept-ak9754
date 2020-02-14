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

#ifndef INCLUDE_AK9754_PARAM_H
#define INCLUDE_AK9754_PARAM_H

/**************************************************************
* hardware-related parameters
* please change the value according to customer's environment
***************************************************************/
/* AK9754 i2c slave address */
#define AK9754_SLAVE_ADR 0x60

/* AK9754 register parameters */
/* ODR bit: valid range is [0x00, 0x03] */
#define AK9754_ODR_VAL_DEP  0x01         /* 2Hz */
/* HBDTH bit: valid range is [0x0000, 0x7fff] ([0, 32767]) */
#define AK9754_HBDTH_VAL 0x012C          /* 300 */

/**************************************************************
* algorithm-related parameters
* please change the value according to customer's environment
***************************************************************/
#define NUMBER_OF_DEPARTURE_COUNTS 3
#define MIN_DELTA 32

/**************************************************************
* hardware-related parameters
* please do not change the value
***************************************************************/
/* CNTL3 values */
/* LNM bit: valid value is 1 or 0 */
#define AK9754_LNM_VAL      1            /* ON */
#define AK9754_LNM_VAL_DEFAULT      0    /* OFF */
/* ODR bit: valid range is [0x00, 0x03] */
#define AK9754_ODR_VAL_APP  0x02         /* 10Hz */
#define AK9754_ODR_VAL_DEFAULT  0x02     /* 10Hz */

/* FCTMP bit: valid range is [0x00, 0x02] */
#define AK9754_FCTMP_VAL_DEFAULT    0x02 /* 0.445Hz */
/* FCIR bit: valid range is [0x00, 0x02] */
#define AK9754_FCIR_VAL_DEFAULT     0x01 /* 0.9Hz */

/* CNTL4 valus */
/* TOPT bit: valid range is [0x00, 0x07] */
#define AK9754_TOPT_VAL     0x00         /* ALL OFF */
#define AK9754_TOPT_VAL_DEFAULT     0x07 /* ALL ON */

/* CNTL5 values */
/* TMPOFS bit: valid range is [0xc0, 0x3f] ([-64, 63]) */
#define AK9754_TMPOFS_VAL_DEFAULT   0x00

/* CNTL6 values */
/* IRGAIN bit: valid range is [0xf0, 0x0f] ([-16, 15]) */
#define AK9754_IRGAIN_VAL_DEFAULT   0x1A

/* CNTL7 values */
/* IRINV bit: valid value is 1 or 0  */
#define AK9754_IRINV_VAL_DEFAULT  0
/* IDLET bit: valid range is [0x00, 0x07] */
#define AK9754_IDLET_VAL_DEFAULT    0x00

/* CNTL8 values */
/* DTCT bit: valid range is [0x00, 0x7f] */
#define AK9754_DTCT_VAL_DEFAULT    0x01

/* CNTL9, 10 values */
/* HBDTH  bit: valid range is [0x0000, 0x7fff] ([0, 32767]) */
#define AK9754_HBDTH_VAL_DEFAULT 0x012C  /* 300 */

#endif /* !defined(INCLUDE_AK9754_PARAM_H) */
