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

#ifndef AK9754_DEVICE_H
#define AK9754_DEVICE_H

/* AK9754 Register definitions */
#define AK9754_WIA1_REG     0x00 /* Company code */
#define AK9754_WIA2_REG     0x01 /* Device ID */
#define AK9754_INFO1_REG    0x02 /* Unused information */
#define AK9754_INFO2_REG    0x03 /* Unused information */
#define AK9754_ST1_REG      0x04 /* Status 1 */
#define AK9754_IRDL_REG     0x05 /* IR sensor data (lower) */
#define AK9754_IRDH_REG     0x06 /* IR sensor data (upper) */
#define AK9754_TMPL_REG     0x07 /* Integrated temperature sensor data (lower) */
#define AK9754_TMPH_REG     0x08 /* Integrated temperature sensor data (upper) */
#define AK9754_ST2_REG      0x09 /* Status 2 */
#define AK9754_ST3_REG      0x0A /* Status 3 */
#define AK9754_SB0L_REG     0x0B /* latest IR sensor data (lower) */
#define AK9754_SB0H_REG     0x0C /* latest IR sensor data (upper) */
#define AK9754_SB1L_REG     0x0D /* previous IR sensor data (lower) */
#define AK9754_SB1H_REG     0x0E /* previous IR sensor data (upper) */
#define AK9754_SB2L_REG     0x0F /* 2 previous IR sensor data (lower) */
#define AK9754_SB2H_REG     0x10 /* 2 previous IR sensor data (upper) */
#define AK9754_SB3L_REG     0x11 /* 3 previous IR sensor data (lower) */
#define AK9754_SB3H_REG     0x12 /* 3 previous IR sensor data (upper) */
#define AK9754_SB4L_REG     0x13 /* 4 previous IR sensor data (lower) */
#define AK9754_SB4H_REG     0x14 /* 4 previous IR sensor data (upper) */
#define AK9754_SB5L_REG     0x15 /* 5 previous IR sensor data (lower) */
#define AK9754_SB5H_REG     0x16 /* 5 previous IR sensor data (upper) */
#define AK9754_SB6L_REG     0x17 /* 6 previous IR sensor data (lower) */
#define AK9754_SB6H_REG     0x18 /* 6 previous IR sensor data (upper) */
#define AK9754_SB7L_REG     0x19 /* 7 previous IR sensor data (lower) */
#define AK9754_SB7H_REG     0x1A /* 7 previous IR sensor data (upper) */
#define AK9754_SB8L_REG     0x1B /* 8 previous IR sensor data (lower) */
#define AK9754_SB8H_REG     0x1C /* 8 previous IR sensor data (upper) */
#define AK9754_SB9L_REG     0x1D /* oldest IR sensor data (lower) */
#define AK9754_SB9H_REG     0x1E /* oldest IR sensor data (lower) */
#define AK9754_ST4_REG      0x1F /* Status 4 */
#define AK9754_CTRL1_REG    0x20 /* Software reset */
#define AK9754_CTRL2_REG    0x21 /* Sync mode setting */
#define AK9754_CTRL3_REG    0x22 /* Lownoise mode / odr /
                                    fctmp / fcir settings */
#define AK9754_CTRL4_REG    0x23 /* Optimization mode settings */
#define AK9754_CTRL5_REG    0x24 /* TMP offset settings */
#define AK9754_CTRL6_REG    0x25 /* IR signal gain settings */
#define AK9754_CTRL7_REG    0x26 /* Invert mode / idling time settings */
#define AK9754_CTRL8_REG    0x27 /* Detection time settings */
#define AK9754_CTRL9_REG    0x28 /* Threshold level settings (lower) */
#define AK9754_CTRL10_REG   0x29 /* Threshold level settings (upper) */
#define AK9754_CTRL11_REG   0x2A /* Enable/Disable settings */
#define AK9754_CTRL12_REG   0x2B /* Measuring mode settings */

/* Register helper values */
#define AK9754_COMPANY_ID   0x48 /* Company ID of AKM */
#define AK9754_DEVICE_ID    0x15 /* Device ID of AK9754 */

#define AK9754_ST1_DRDY     0x01 /* bit mask of DRDY for ST1 */
#define AK9754_ST1_HBDR1    0x10 /* bit mask of HBDR1 for ST1 */
#define AK9754_ST3_HBDR3    0x10 /* bit mask of HBDR3 for ST3 */
#define AK9754_ST3_SBNMB    0x0f /* bit mask of SBNMB for ST3 */

#define AK9754_CTRL1_SRST 1      /* bit mask of SRST for CTRL1 */

#define AK9754_CTRL3_FCIR_SHIFT  0
#define AK9754_CTRL3_FCTMP_SHIFT 2
#define AK9754_CTRL3_ODR_SHIFT   4
#define AK9754_CTRL3_LNM_SHIFT   6
/* helper function to make CTRL3 register's value */
#define AK9754_CTRL3(lnmode, odr, tmpfc, irdfc) \
    ((lnmode) << (AK9754_CTRL3_LNM_SHIFT) | \
     (odr) << (AK9754_CTRL3_ODR_SHIFT) | \
     (tmpfc) << (AK9754_CTRL3_FCTMP_SHIFT) | \
     (irdfc) << (AK9754_CTRL3_FCIR_SHIFT))

#define AK9754_CTRL7_IRINV_SHIFT   3
#define AK9754_CTRL7_IDLET_SHIFT 0
/* helper function to make CTRL7 register's value */
#define AK9754_CTRL7(irinv, idlet) \
    ((irinv) << (AK9754_CTRL7_IRINV_SHIFT) | \
     (idlet) << (AK9754_CTRL7_IDLET_SHIFT))

/* helper function to make CTRL9 / CTRL10 register's value */
#define AK9754_CTRL9(thld) ((thld) & 0xff)
#define AK9754_CTRL10(thld) (((thld) & 0xff00) >> 8)

#define AK9754_CNTL11_DRIEN  0x01
#define AK9754_CNTL11_HBDIEN 0x02
#define AK9754_CNTL11_SBEN   0x04
#define AK9754_CNTL11_SBHBD  0x08
#define AK9754_CNTL11_HBDEN  0x10

#define AK9754_CTRL12_MODE_STANDBY 0x00   /* Standby mode */
#define AK9754_CTRL12_MODE_MEASURE 0x01   /* Continuous measurement mode */

#define AK9754_PSUP_PORT_IN_MSEC 51

/* ST1, IRL, IRH, TMPL, TMPH, ST2 */
#define NUM_OF_BYTES_IR_BLK 6
/* ST3, SB0L, SB0H, ..., SB9L, SB9H, ST4 */
#define NUM_OF_BYTES_STREAMING_BUF_BLK 22

#endif  /* AK9754_DEVICE_H */
