#ifndef DAC_H__
#define DAC_H__

#include "sl_spidrv_instances.h"
#include "sl_spidrv_usart_spi_dac_config.h"

/**
 * Writes a raw value to the DAC. DAC's VOUT will be (value/0xFFFF)*V_3v3
 *
 * Note about V_3v3... the sensor's voltage regulator is designed to put out 3.35V
 *    However, if the regulator has been bypassed, then this voltage is tied directly
 *    to the battery and may be variable. Plan accordingly.
 *
 * @param value
 */
void writeValueToDAC(const uint16_t value);

#endif
