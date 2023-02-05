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

#define DAC_MAX_VALUE 0xFFFFu

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

/**
 * Returns the last value sent to the DAC. This isn't guaranteed to be the
 * actual value of the DAC ... it's certainly possible that sending the value
 * to the DAC failed somehow. I don't know how it could have, but it's possible.
 *
 * Not sure if we can read the value from the DAC? We'll look at that later.
 *
 * @return
 */
uint16_t getLastValueWritten();

#endif
