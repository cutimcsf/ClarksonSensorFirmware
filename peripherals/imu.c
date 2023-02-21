/*
 *  peripherals/imu.c
 *
 *  Created on: February 16, 2023
 *      Author: Timothy C. Sweeney-Fanelli
 *              Affects AI
 *              tim@affects.ai
 *
 *  Methods for interacting with the ADXL362 IMU chip.
 ******************************************************************************/

#include "imu.h"
#include "app_assert.h"

#define TX_BUFFER_SIZE 3
#define RX_BUFFER_SIZE (TX_BUFFER_SIZE+6)

uint8_t TxBuffer[TX_BUFFER_SIZE] = {0x00, 0x00, 0x00};
uint8_t RxBuffer[RX_BUFFER_SIZE];

volatile int16_t x_data;
volatile int16_t y_data;
volatile int16_t z_data;

//uint8_t* readFIFO() {
//  Ecode_t retVal;
//  TxBuffer[0] = IMU_COMMAND_READ_REGISTER;
//
//  for ( int i = 0; i < RX_BUFFER_SIZE; ++i ) RxBuffer[i] = 0x00;
//
//  retVal = SPIDRV_MTransferB(sl_spidrv_usart_spi_accel_handle, TxBuffer, RxBuffer, 7);
//  app_assert(retVal == ECODE_OK);
//
//  return &RxBuffer[1];
//}

/**
 * Performs a multi-byte read beginning at startAddress
 *
 * @param startAddress
 * @param bytesToRead
 * @return
 */
uint8_t* multiByteRead(uint8_t startAddress, uint8_t bytesToRead) {
  Ecode_t retVal;
  TxBuffer[0] = IMU_COMMAND_READ_REGISTER;
  TxBuffer[1] = startAddress;

  for ( int i = 0; i < RX_BUFFER_SIZE; ++i )
    RxBuffer[i] = 0x00;

  retVal = SPIDRV_MTransferB(sl_spidrv_usart_spi_accel_handle, TxBuffer, RxBuffer, bytesToRead+2);
  app_assert(retVal == ECODE_OK);

  return &RxBuffer[2];
}

/**
 * Writes a single byte to the specified register address.
 *
 * @param registerAddress
 * @param value
 */
void writeToRegister(const uint8_t registerAddress, const uint8_t value) {
  Ecode_t retVal;

  TxBuffer[0] = IMU_COMMAND_WRITE_REGISTER;
  TxBuffer[1] = registerAddress;
  TxBuffer[2] = value;

  retVal = SPIDRV_MTransmitB(sl_spidrv_usart_spi_accel_handle, TxBuffer, 3);
  app_assert(retVal == ECODE_OK);
}

void IMU_reset() {
  writeToRegister(IMU_REGISTER_SOFT_RESET, 0x52);

  // Per data sheet, 0.5ms delay required after soft_reset.
  sl_sleeptimer_delay_millisecond(1);
}

void IMU_initialize() {
  // Per data sheet, device configuration procedure is as follows:
  // 1. Set activity and inactivity thresholds (regs 0x20 to 0x26)
  // 2. Configure activity and inactivity functions (reg 0x27)
  // 3. Configure the FIFO (reg 0x28 and 0x29)
  // 4. Map interupts (reg 0x2A and 0x2B)
  // 5. Configure generate device settings (reg 0x2C)
  // 6. Turn measurement on (0x2D)

  IMU_reset();

  const uint16_t ACTIVITY_THRESHOLD = 250;    // 250mg
  writeToRegister(IMU_REGISTER_THRESH_ACT_L, (uint8_t) ACTIVITY_THRESHOLD & 0x00FF);
  writeToRegister(IMU_REGISTER_THRESH_ACT_H, (uint8_t) (ACTIVITY_THRESHOLD & 0xFF00)>>8);

  const uint16_t INACTIVITY_THRESHOLD = 150;  // 150mg
  writeToRegister(IMU_REGISTER_THRESH_INACT_L, (uint8_t) INACTIVITY_THRESHOLD & 0x00FF);
  writeToRegister(IMU_REGISTER_THRESH_INACT_H, (uint8_t) (INACTIVITY_THRESHOLD & 0xFF00)>>8);

  const uint16_t INACTIVITY_TIMEOUT = 30;     // 30 samples, approx 5s
  writeToRegister(IMU_REGISTER_TIME_INACT_L, (uint8_t) INACTIVITY_TIMEOUT & 0x00FF);
  writeToRegister(IMU_REGISTER_TIME_INACT_H, (uint8_t) (INACTIVITY_TIMEOUT & 0xFF00)>>8);

  const uint8_t MOTION_DETECT = 0x3F;
  writeToRegister(IMU_REGISTER_ACT_INACT_CTL, MOTION_DETECT);

  const uint8_t FIFO_MODE = 0x02u;
  writeToRegister(IMU_REGISTER_FIFO_CONTROL, FIFO_MODE);

  const uint8_t MEASURE_MODE = 0x02;
  writeToRegister(IMU_REGISTER_STATUS, MEASURE_MODE);
}

void IMU_refreshValues() {
  /*
   * Reads 6-bytes of data beginning at register address 0x0E, which spans:
   *  0x0E - IMU_REGISTER_XDATA_L
   *  0x0F - IMU_REGISTER_XDATA_H
   *  0x10 - IMU_REGISTER_YDATA_L
   *  0x11 - IMU_REGISTER_YDATA_H
   *  0x12 - IMU_REGISTER_ZDATA_L (LSB)
   *  0x13 - IMU_REGISTER_ZDATA_H (MSB)
   */

  uint8_t *data = multiByteRead(IMU_REGISTER_XDATA_L,  6); //readFIFO();
  x_data = data[0] | (data[1]<<8);
  y_data = data[2] | (data[3]<<8);
  z_data = data[4] | (data[5]<<8);

}

void IMU_getCurrentValues(int16_t *x, int16_t *y, int16_t *z) {
  *x = x_data;
  *y = y_data;
  *z = z_data;
}
