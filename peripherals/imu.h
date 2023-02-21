/*
 *  peripherals/imu.h
 *
 *  Created on: February 16, 2023
 *      Author: Timothy C. Sweeney-Fanelli
 *              Affects AI
 *              tim@affects.ai
 *
 *  Methods for interacting with the ADXL362 IMU chip.
 *  https://www.analog.com/media/en/technical-documentation/data-sheets/ADXL362.pdf
 ******************************************************************************/

#ifndef PERIPHERALS_IMU_H_
#define PERIPHERALS_IMU_H_

#include "sl_spidrv_instances.h"
#include "sl_spidrv_usart_spi_accel_config.h"

/**
 * IMU SPI COMMANDS
 * Defined in datasheet on page 19
 */
#define IMU_COMMAND_WRITE_REGISTER  0x0Au
#define IMU_COMMAND_READ_REGISTER   0x0Bu
#define IMU_COMMAND_READ_FIFO       0x0Du

/**
 * IMU Registers, read/write via SPI commands
 * Defined in datasheet on page 23
 */
#define IMU_REGISTER_STATUS         0x0Bu
#define IMU_REGISTER_XDATA_L        0x0Eu
#define IMU_REGISTER_XDATA_H        0x0Fu
#define IMU_REGISTER_YDATA_L        0x10u
#define IMU_REGISTER_YDATA_H        0x11u
#define IMU_REGISTER_ZDATA_L        0x12u
#define IMU_REGISTER_ZDATA_H        0x13u
#define IMU_REGISTER_TEMP_L         0x14u
#define IMU_REGISTER_TEMP_H         0x15u
#define IMU_REGISTER_SOFT_RESET     0x1Fu
#define IMU_REGISTER_THRESH_ACT_L   0x20u
#define IMU_REGISTER_THRESH_ACT_H   0x21u
#define IMU_REGISTER_TIME_ACT       0x22u
#define IMU_REGISTER_THRESH_INACT_L 0x23u
#define IMU_REGISTER_THRESH_INACT_H 0x24u
#define IMU_REGISTER_TIME_INACT_L   0x25u
#define IMU_REGISTER_TIME_INACT_H   0x26u
#define IMU_REGISTER_ACT_INACT_CTL  0x27u
#define IMU_REGISTER_FIFO_CONTROL   0x28u
#define IMU_REGISTER_FIFO_SAMPLES   0x29u
#define IMU_REGISTER_INTMAP1        0x2Au
#define IMU_REGISTER_INTMAP2        0x2Bu
#define IMU_REGISTER_FILTER_CTL     0x2Cu
#define IMU_REGISTER_POWER_CONTROL  0x2Du

/**
 * Performs a soft reset on the IMU
 */
void IMU_reset();

/**
 * Initialize the ADXL362 IMU Unit for Operations
 * Sets the following:
 *  - Activity Threshold: 250 mg
 *  - Inactivity Threshold: 150 mg
 *  - Inactivity Timeout: 30 samples
 *  - Loop Mode (activity and inactivity linked sequentially)
 *  - FIFO Mode - Stream (not currently using FIFO)
 *  - Measure Mode: enabled
 */
void IMU_initialize();

/**
 * Refreshes the current values from the IMU
 */
void IMU_refreshValues();

/**
 * Obtains the most recently read values from the IMU (call IMU_refreshValues to
 * read the latest directly from the device)
 *
 * @param x [out]
 * @param y [out]
 * @param z [out]
 */
void IMU_getCurrentValues(int16_t *x, int16_t *y, int16_t *z);

#endif /* PERIPHERALS_IMU_H_ */
