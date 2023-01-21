/*
 *  peripherals/dac.c
 *
 *  Created on: January 21, 2023
 *      Author: Timothy C. Sweeney-Fanelli
 *              Affects AI
 *              tim@affects.ai
 *
 *  Methods for interacting with the DAC8330 chips.
 ******************************************************************************/

#include "dac.h"

/**
 * DAC's interface is very simple -- it takes a single 16-bit value from 0x0000
 * through 0xFFFF. The DAC's V_out will be it's V_in * (value / 0xFFFF)
 *
 * @param value
 */
void DAC_writeValue(const uint16_t value) {
  SPIDRV_MTransmitB(sl_spidrv_usart_spi_dac_handle, &value, 1);
}
