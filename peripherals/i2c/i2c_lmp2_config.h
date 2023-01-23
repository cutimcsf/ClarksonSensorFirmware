/*
 *  peripherals/i2c/i2c_lmp2_config.h
 *
 *  Created on: January 21, 2023
 *      Author: Timothy C. Sweeney-Fanelli
 *              Affects AI
 *              tim@affects.ai
 *
 *  Pin and ABUS parameters for LMP91000_2.
 */

#ifndef I2C_LMP2_CONFIG_H
#define I2C_LMP2_CONFIG_H

#include <em_gpio.h>

#define LMP91000_2_TEMPERATURE_PORT    gpioPortA
#define LMP91000_2_TEMPERATURE_PIN     3
#define LMP91000_2_ENLOW_PORT          gpioPortA
#define LMP91000_2_ENLOW_PIN           2

// <o I2C_LMP2_REFERENCE_CLOCK> Reference clock frequency
// <i> Frequency in Hz of the reference clock.
// <i> Select 0 to use the frequency of the currently selected clock.
// <i> Default: 0
#define I2C_LMP2_REFERENCE_CLOCK 0

// <o I2C_LMP2_SPEED_MODE> Speed mode
// <0=> Standard mode (100kbit/s)
// <1=> Fast mode (400kbit/s)
// <2=> Fast mode plus (1Mbit/s)
// <i> Default: 0
#define I2C_LMP2_SPEED_MODE      0

#define I2C_LMP2_PERIPHERAL            I2C0
#define I2C_LMP2_PERIPHERAL_NO         0

// I2C0 SCL on PB12
#define I2C_LMP2_SCL_PORT              gpioPortA
#define I2C_LMP2_SCL_PIN               1
#define I2C_LMP2_SCL_LOC               0

// I2C0 SDA on PB11
#define I2C_LMP2_SDA_PORT              gpioPortA
#define I2C_LMP2_SDA_PIN               0
#define I2C_LMP2_SDA_LOC               0

#endif // I2C_LMP2_CONFIG_H
