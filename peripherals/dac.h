/*
 *  peripherals/dac.h
 *
 *  Created on: January 21, 2023
 *      Author: Timothy C. Sweeney-Fanelli
 *              Affects AI
 *              tim@affects.ai
 *
 *  Methods for interacting with the DAC8330 chip.
 ******************************************************************************/

#ifndef DAC_H__
#define DAC_H__

#include "sl_spidrv_instances.h"
#include "sl_spidrv_usart_spi_dac_config.h"

/******************************************************************************
 * Writes a raw value to the DAC. DAC's VOUT will be (value/0xFFFF)*V_3v3
 *
 * Note about V_3v3... the sensor's voltage regulator is designed to put out 3.35V
 *    However, if the regulator has been bypassed, then this voltage is tied directly
 *    to the battery and may be variable. Plan accordingly.
 *
 * The DAC's Vout is the reference voltage supplied to the two LMP91000 chips
 * on the PCB.
 *
 * @param value
 *****************************************************************************/
void DAC_writeValue(const uint16_t value);

#endif
