/*
 * lmp_config.h
 *
 *  Created on: Jan 20, 2023
 *      Author: tim
 */

#ifndef LMP_CONFIG_H_
#define LMP_CONFIG_H_

#include "i2c_lmp1_config.h"
#include "i2c_lmp2_config.h"
#include "sl_i2cspm.h"
#include "em_cmu.h"


#if I2C_LMP1_SPEED_MODE == 0
#define I2C_LMP1_HLR i2cClockHLRStandard
#define I2C_LMP1_MAX_FREQ I2C_FREQ_STANDARD_MAX
#elif I2C_LMP1_SPEED_MODE == 1
#define I2C_LMP1_HLR i2cClockHLRAsymetric
#define I2C_LMP1_MAX_FREQ I2C_FREQ_FAST_MAX
#elif I2C_LMP1_SPEED_MODE == 2
#define I2C_LMP1_HLR i2cClockHLRFast
#define I2C_LMP1_MAX_FREQ I2C_FREQ_FASTPLUS_MAX
#endif

#if I2C_LMP2_SPEED_MODE == 0
#define I2C_LMP2_HLR i2cClockHLRStandard
#define I2C_LMP2_MAX_FREQ I2C_FREQ_STANDARD_MAX
#elif I2C_LMP2_SPEED_MODE == 1
#define I2C_LMP2_HLR i2cClockHLRAsymetric
#define I2C_LMP2_MAX_FREQ I2C_FREQ_FAST_MAX
#elif I2C_LMP2_SPEED_MODE == 2
#define I2C_LMP2_HLR i2cClockHLRFast
#define I2C_LMP2_MAX_FREQ I2C_FREQ_FASTPLUS_MAX
#endif

extern sl_i2cspm_t *i2c_lmp1;
extern sl_i2cspm_t *i2c_lmp2;
extern I2CSPM_Init_TypeDef init_lmp1;
extern I2CSPM_Init_TypeDef init_lmp2;

#endif /* LMP_CONFIG_H_ */
