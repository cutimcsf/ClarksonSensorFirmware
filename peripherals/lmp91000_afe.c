/*
 *  peripherals/lmp91000.c
 *
 *  Created on: January 21, 2023
 *      Author: Timothy C. Sweeney-Fanelli
 *              Affects AI
 *              tim@affects.ai
 *
 *  Methods for interacting with the LMP91000 chips.
 *
 *  DataSheet:
 *    https://www.ti.com/lit/ds/symlink/lmp91000.pdf
 ******************************************************************************/

#include "lmp91000_afe.h"
#include "adc.h"

#include <app_assert.h>
#include <em_i2c.h>


// The LMP91000's I2C Address and internal register addresses as defined
//  by the datasheet -- section 7.5.1 and 7.5.3
#define LMP91000_I2C_ADDRESS                   0b10010000
#define LMP91000_STATUS_REG_ADDY               0x00
#define LMP91000_LOCK_REG_ADDY                 0x01
#define LMP91000_TIACN_REG_ADDY                0x10
#define LMP91000_REFCN_REG_ADDY                0x11
#define LMP91000_MDOECN_REG_ADDY               0x12

#define I2C_RXBUFFER_SIZE                 1
#define I2C_TXBUFFER_SIZE                 2

LMP91000_Config *activeConfig;

// Buffers++
uint8_t i2c_txBuffer[I2C_TXBUFFER_SIZE];
uint8_t i2c_rxBuffer[I2C_RXBUFFER_SIZE];
uint8_t i2c_rxBufferIndex;

void LMP91000_enableSensor(const LMP91000_Selector sel) {
  LMP91000_Config *disableConfig;

  switch( sel ) {
    case LMP91000_1:
      activeConfig = &lmp91000_config_1;
      disableConfig = &lmp91000_config_2;
      break;

    case LMP91000_2:
      activeConfig = &lmp91000_config_2;
      disableConfig = &lmp91000_config_1;
      break;

    default:
      app_assert(false, "Invalid LMP9100_Selector value. Unable to proceed.");
      break;
  }

  CMU_ClockEnable(cmuClock_GPIO, true);


  GPIO_PinModeSet(activeConfig->enlow_port, activeConfig->enlow_pin, gpioModeInputPull, 0);
  GPIO_PinModeSet(disableConfig->enlow_port, disableConfig->enlow_pin, gpioModeInputPull, 0);

  // This wouldn't be needed if I put them on the same i2c bus but I wasn't
  // paying attention ;).
  I2CSPM_Init(activeConfig->i2c_init);

}

/**
 * Reference section 7.5.2 of the data sheet for an overview of what's happening
 * here ... write operations include:
 *    7-bit slave address
 *    1-bit r/w flag
 *    8-bit internal register address
 *    8-bit value to write to the register
 *
 * @param registerAddy
 * @param data
 */
void LMP91000_sendData(const uint8_t registerAddy, const uint8_t data) {
  I2C_TransferSeq_TypeDef i2cTransfer;
  I2C_TransferReturn_TypeDef result;

  i2c_txBuffer[0] = registerAddy;
  i2c_txBuffer[1] = data;

  // Initializing I2C transfer
  i2cTransfer.addr          = LMP91000_I2C_ADDRESS;
  i2cTransfer.flags          = I2C_FLAG_WRITE;
  i2cTransfer.buf[0].data   = i2c_txBuffer;
  i2cTransfer.buf[0].len    = 2;
  i2cTransfer.buf[1].data   = i2c_rxBuffer;
  i2cTransfer.buf[1].len    = I2C_RXBUFFER_SIZE;
  result = I2CSPM_Transfer(activeConfig->i2c_init->port, &i2cTransfer);
  app_assert(result == i2cTransferDone);
}

/**
 * Reference section 7.5.2 of the data sheet for an overview of what's happening
 * here ... read operations are two steps:
 *  1. Write the internal register address with no value, then
 *  2. Read the internal register
 *
 * So first we perform a write exactly as we do above in sendData, but we omit
 * the last byte:
 *    7-bit slave address
 *    1-bit r/w flag
 *    8-bit internal register address
 *
 * Then we perform a second transfer setting the flag to I2C_FLAG_READ.
 *
 * When the i2c transfer is complete, the read value should be in
 * i2c_rxBuffer[0]
 *
 * @param registerAddy
 * @return
 */
uint8_t LMP91000_readData(const uint8_t registerAddy) {
  I2C_TransferSeq_TypeDef i2cTransfer;
  I2C_TransferReturn_TypeDef result;

  i2c_txBuffer[0] = registerAddy;
  i2c_txBuffer[1] = 0;

  // Initializing I2C transfer -- write the register address we want to read
  i2cTransfer.addr          = LMP91000_I2C_ADDRESS;
  i2cTransfer.flags         = I2C_FLAG_WRITE_READ;
  i2cTransfer.buf[0].data   = i2c_txBuffer;
  i2cTransfer.buf[0].len    = 1;
  i2cTransfer.buf[1].data   = i2c_rxBuffer;
  i2cTransfer.buf[1].len    = I2C_RXBUFFER_SIZE;

  result = I2CSPM_Transfer(activeConfig->i2c_init->port, &i2cTransfer);
  app_assert(result == i2cTransferDone);
  return i2c_rxBuffer[0];
}

void LMP91000_setOpMode(uint8_t shortEnabled, uint8_t opMode) {
  uint8_t data = GET_OPMODE_VALUE(shortEnabled, opMode);
  LMP91000_sendData(LMP91000_MODECN_REG_ADDY, data);
}

void LMP91000_getOpMode(uint8_t *feShortEnabled, uint8_t *opMode) {
  uint8_t data = LMP91000_readData(LMP91000_MODECN_REG_ADDY);
  *feShortEnabled = GET_OPMODE_SHORT_EN(data);
  *opMode = GET_OPMODE_MODE(data);
}

void LMP91000_setRefCN(uint8_t source, uint8_t intz, uint8_t sign, uint8_t bias) {
  uint8_t data = GET_REFCN_REG_VALUE(source, intz, sign, bias);
  LMP91000_sendData(LMP91000_REFCN_REG_ADDY, data);
}

void LMP91000_getRefCN(uint8_t *source, uint8_t *intz, uint8_t *sign, uint8_t *bias) {
  uint8_t data = LMP91000_readData(LMP91000_REFCN_REG_ADDY);
  *source = GET_REFCN_SOURCE(data);
  *intz = GET_REFCN_INT_Z(data);
  *sign = GET_REFCN_BIAS_SIGN(data);
  *bias = GET_REFCN_BIAS_MAGNITUDE(data);
}

void LMP91000_setTIACN(uint8_t gain, uint8_t rload) {
  uint8_t data = GET_TIA_REG_VALUE(gain,rload);
  LMP91000_sendData(LMP91000_TIACN_REG_ADDY, data);
}

void LMP91000_getTIACN(uint8_t *gain, uint8_t *rload) {
  uint8_t data = LMP91000_readData(LMP91000_TIACN_REG_ADDY);
  *gain = GET_TIA_GAIN(data);
  *rload = GET_TIA_RLOAD(data);
}

void LMP91000_setLock(uint8_t value) {
  LMP91000_sendData(LMP91000_LOCK_REG_ADDY, value);
}

void LMP91000_getLock(uint8_t *value) {
  *value = LMP91000_readData(LMP91000_LOCK_REG_ADDY);
}

void LMP91000_getStatus(uint8_t *value) {
  *value = LMP91000_readData(LMP91000_STATUS_REG_ADDY);
}

uint32_t LMP91000_getValue() {
  return ADC_readPin(activeConfig->adcDataPin);
}
