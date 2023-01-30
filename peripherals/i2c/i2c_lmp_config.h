/*
 *  peripherals/i2c/i2c_lmp_config.h
 *
 *  Created on: January 21, 2023
 *      Author: Timothy C. Sweeney-Fanelli
 *              Affects AI
 *              tim@affects.ai
 *
 *  I2C Initialization values for the two LMP91000 chips.
 */

#ifndef LMP_CONFIG_H_
#define LMP_CONFIG_H_

#include "i2c_lmp1_config.h"
#include "i2c_lmp2_config.h"
#include "sl_i2cspm.h"
#include <em_cmu.h>


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

typedef struct {
  sl_i2cspm_t          *i2c_lmp;
  I2CSPM_Init_TypeDef  *i2c_init;
  uint8_t               enlow_port;
  uint8_t               enlow_pin;
  uint8_t               temperature_port;
  uint8_t               temperature_pin;
  uint32_t              adcDataPin;
} LMP91000_Config;

extern LMP91000_Config lmp91000_config_1;
extern LMP91000_Config lmp91000_config_2;

#endif /* LMP_CONFIG_H_ */
