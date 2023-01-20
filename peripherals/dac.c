#include <peripherals/dac.h>

void writeValueToDAC(const uint16_t value) {
  SPIDRV_MTransmitB(sl_spidrv_usart_spi_dac_handle, &value, 1);
}
