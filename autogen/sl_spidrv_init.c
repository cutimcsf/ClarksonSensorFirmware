#include "spidrv.h"
#include "sl_spidrv_instances.h"
#include "sl_assert.h"


#include "sl_spidrv_usart_spi_accel_config.h"
#include "sl_spidrv_usart_spi_dac_config.h"

SPIDRV_HandleData_t sl_spidrv_usart_spi_accel_handle_data;
SPIDRV_Handle_t sl_spidrv_usart_spi_accel_handle = &sl_spidrv_usart_spi_accel_handle_data;

SPIDRV_HandleData_t sl_spidrv_usart_spi_dac_handle_data;
SPIDRV_Handle_t sl_spidrv_usart_spi_dac_handle = &sl_spidrv_usart_spi_dac_handle_data;

SPIDRV_Init_t sl_spidrv_usart_init_spi_accel = {
  .port = SL_SPIDRV_USART_SPI_ACCEL_PERIPHERAL,
#if defined(_USART_ROUTELOC0_MASK)
  .portLocationTx = SL_SPIDRV_USART_SPI_ACCEL_TX_LOC,
  .portLocationRx = SL_SPIDRV_USART_SPI_ACCEL_RX_LOC,
  .portLocationClk = SL_SPIDRV_USART_SPI_ACCEL_CLK_LOC,
#if defined(SL_SPIDRV_USART_SPI_ACCEL_CS_LOC)
  .portLocationCs = SL_SPIDRV_USART_SPI_ACCEL_CS_LOC,
#endif
#elif defined(_GPIO_USART_ROUTEEN_MASK)
  .portTx = SL_SPIDRV_USART_SPI_ACCEL_TX_PORT,
  .portRx = SL_SPIDRV_USART_SPI_ACCEL_RX_PORT,
  .portClk = SL_SPIDRV_USART_SPI_ACCEL_CLK_PORT,
#if defined(SL_SPIDRV_USART_SPI_ACCEL_CS_PORT)
  .portCs = SL_SPIDRV_USART_SPI_ACCEL_CS_PORT,
#endif
  .pinTx = SL_SPIDRV_USART_SPI_ACCEL_TX_PIN,
  .pinRx = SL_SPIDRV_USART_SPI_ACCEL_RX_PIN,
  .pinClk = SL_SPIDRV_USART_SPI_ACCEL_CLK_PIN,
#if defined(SL_SPIDRV_USART_SPI_ACCEL_CS_PIN)
  .pinCs = SL_SPIDRV_USART_SPI_ACCEL_CS_PIN,
#endif
#else
  .portLocation = SL_SPIDRV_USART_SPI_ACCEL_ROUTE_LOC,
#endif
  .bitRate = SL_SPIDRV_USART_SPI_ACCEL_BITRATE,
  .frameLength = SL_SPIDRV_USART_SPI_ACCEL_FRAME_LENGTH,
  .dummyTxValue = 0,
  .type = SL_SPIDRV_USART_SPI_ACCEL_TYPE,
  .bitOrder = SL_SPIDRV_USART_SPI_ACCEL_BIT_ORDER,
  .clockMode = SL_SPIDRV_USART_SPI_ACCEL_CLOCK_MODE,
  .csControl = SL_SPIDRV_USART_SPI_ACCEL_CS_CONTROL,
  .slaveStartMode = SL_SPIDRV_USART_SPI_ACCEL_SLAVE_START_MODE,
};

SPIDRV_Init_t sl_spidrv_usart_init_spi_dac = {
  .port = SL_SPIDRV_USART_SPI_DAC_PERIPHERAL,
#if defined(_USART_ROUTELOC0_MASK)
  .portLocationTx = SL_SPIDRV_USART_SPI_DAC_TX_LOC,
  .portLocationRx = SL_SPIDRV_USART_SPI_DAC_RX_LOC,
  .portLocationClk = SL_SPIDRV_USART_SPI_DAC_CLK_LOC,
#if defined(SL_SPIDRV_USART_SPI_DAC_CS_LOC)
  .portLocationCs = SL_SPIDRV_USART_SPI_DAC_CS_LOC,
#endif
#elif defined(_GPIO_USART_ROUTEEN_MASK)
  .portTx = SL_SPIDRV_USART_SPI_DAC_TX_PORT,
  .portRx = SL_SPIDRV_USART_SPI_DAC_RX_PORT,
  .portClk = SL_SPIDRV_USART_SPI_DAC_CLK_PORT,
#if defined(SL_SPIDRV_USART_SPI_DAC_CS_PORT)
  .portCs = SL_SPIDRV_USART_SPI_DAC_CS_PORT,
#endif
  .pinTx = SL_SPIDRV_USART_SPI_DAC_TX_PIN,
  .pinRx = SL_SPIDRV_USART_SPI_DAC_RX_PIN,
  .pinClk = SL_SPIDRV_USART_SPI_DAC_CLK_PIN,
#if defined(SL_SPIDRV_USART_SPI_DAC_CS_PIN)
  .pinCs = SL_SPIDRV_USART_SPI_DAC_CS_PIN,
#endif
#else
  .portLocation = SL_SPIDRV_USART_SPI_DAC_ROUTE_LOC,
#endif
  .bitRate = SL_SPIDRV_USART_SPI_DAC_BITRATE,
  .frameLength = SL_SPIDRV_USART_SPI_DAC_FRAME_LENGTH,
  .dummyTxValue = 0,
  .type = SL_SPIDRV_USART_SPI_DAC_TYPE,
  .bitOrder = SL_SPIDRV_USART_SPI_DAC_BIT_ORDER,
  .clockMode = SL_SPIDRV_USART_SPI_DAC_CLOCK_MODE,
  .csControl = SL_SPIDRV_USART_SPI_DAC_CS_CONTROL,
  .slaveStartMode = SL_SPIDRV_USART_SPI_DAC_SLAVE_START_MODE,
};

void sl_spidrv_init_instances(void) {
#if !defined(SL_SPIDRV_USART_SPI_ACCEL_CS_PIN)
  EFM_ASSERT(sl_spidrv_usart_init_spi_accel.csControl == spidrvCsControlAuto);
#endif
#if !defined(SL_SPIDRV_USART_SPI_DAC_CS_PIN)
  EFM_ASSERT(sl_spidrv_usart_init_spi_dac.csControl == spidrvCsControlAuto);
#endif
  SPIDRV_Init(sl_spidrv_usart_spi_accel_handle, &sl_spidrv_usart_init_spi_accel);
  SPIDRV_Init(sl_spidrv_usart_spi_dac_handle, &sl_spidrv_usart_init_spi_dac);
}
