/*
 *  peripherals/i2c/i2c_lmp1_config.h
 *
 *  Created on: January 21, 2023
 *      Author: Timothy C. Sweeney-Fanelli
 *              Affects AI
 *              tim@affects.ai
 *
 *  Pin and ABUS parameters for LMP91000_1.
 */

#ifndef I2C_LMP1_CONFIG_H
#define I2C_LMP1_CONFIG_H

#include <em_gpio.h>

// <o I2C_LMP1_REFERENCE_CLOCK> Reference clock frequency
// <i> Frequency in Hz of the reference clock.
// <i> Select 0 to use the frequency of the currently selected clock.
// <i> Default: 0
#define I2C_LMP1_REFERENCE_CLOCK 0

// <o I2C_LMP1_SPEED_MODE> Speed mode
// <0=> Standard mode (100kbit/s)
// <1=> Fast mode (400kbit/s)
// <2=> Fast mode plus (1Mbit/s)
// <i> Default: 0
#define I2C_LMP1_SPEED_MODE      0

#define I2C_LMP1_PERIPHERAL            I2C0
#define I2C_LMP1_PERIPHERAL_NO         0

// I2C0 SCL on PB12
#define I2C_LMP1_SCL_PORT              gpioPortB
#define I2C_LMP1_SCL_PIN               12
#define I2C_LMP1_SCL_LOC               6

// I2C0 SDA on PB11
#define I2C_LMP1_SDA_PORT              gpioPortB
#define I2C_LMP1_SDA_PIN               11
#define I2C_LMP1_SDA_LOC               6

#endif
