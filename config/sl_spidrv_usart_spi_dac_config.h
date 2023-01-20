/***************************************************************************//**
 * @file
 * @brief SPIDRV_USART Config
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#ifndef SL_SPIDRV_USART_SPI_DAC_CONFIG_H
#define SL_SPIDRV_USART_SPI_DAC_CONFIG_H

#include "spidrv.h"

// <<< Use Configuration Wizard in Context Menu >>>
// <h> SPIDRV settings

// <o SL_SPIDRV_USART_SPI_DAC_BITRATE> SPI bitrate
// <i> Default: 1000000
#define SL_SPIDRV_USART_SPI_DAC_BITRATE           1000000

// <o SL_SPIDRV_USART_SPI_DAC_FRAME_LENGTH> SPI frame length <4-16>
// <i> Default: 8
#define SL_SPIDRV_USART_SPI_DAC_FRAME_LENGTH      8

// <o SL_SPIDRV_USART_SPI_DAC_TYPE> SPI mode
// <spidrvMaster=> Master
// <spidrvSlave=> Slave
#define SL_SPIDRV_USART_SPI_DAC_TYPE              spidrvMaster

// <o SL_SPIDRV_USART_SPI_DAC_BIT_ORDER> Bit order on the SPI bus
// <spidrvBitOrderLsbFirst=> LSB transmitted first
// <spidrvBitOrderMsbFirst=> MSB transmitted first
#define SL_SPIDRV_USART_SPI_DAC_BIT_ORDER         spidrvBitOrderMsbFirst

// <o SL_SPIDRV_USART_SPI_DAC_CLOCK_MODE> SPI clock mode
// <spidrvClockMode0=> SPI mode 0: CLKPOL=0, CLKPHA=0
// <spidrvClockMode1=> SPI mode 1: CLKPOL=0, CLKPHA=1
// <spidrvClockMode2=> SPI mode 2: CLKPOL=1, CLKPHA=0
// <spidrvClockMode3=> SPI mode 3: CLKPOL=1, CLKPHA=1
#define SL_SPIDRV_USART_SPI_DAC_CLOCK_MODE        spidrvClockMode0

// <o SL_SPIDRV_USART_SPI_DAC_CS_CONTROL> SPI master chip select (CS) control scheme.
// <spidrvCsControlAuto=> CS controlled by the SPI driver
// <spidrvCsControlApplication=> CS controlled by the application
#define SL_SPIDRV_USART_SPI_DAC_CS_CONTROL        spidrvCsControlAuto

// <o SL_SPIDRV_USART_SPI_DAC_SLAVE_START_MODE> SPI slave transfer start scheme
// <spidrvSlaveStartImmediate=> Transfer starts immediately
// <spidrvSlaveStartDelayed=> Transfer starts when the bus is idle (CS deasserted)
// <i> Only applies if instance type is spidrvSlave
#define SL_SPIDRV_USART_SPI_DAC_SLAVE_START_MODE  spidrvSlaveStartImmediate
// </h>
// <<< end of configuration section >>>

// <<< sl:start pin_tool >>>
// <usart signal=TX,RX,CLK,(CS)> SL_SPIDRV_USART_SPI_DAC
// $[USART_SL_SPIDRV_USART_SPI_DAC]
#define SL_SPIDRV_USART_SPI_DAC_PERIPHERAL       USART1
#define SL_SPIDRV_USART_SPI_DAC_PERIPHERAL_NO    1

// USART1 TX on PC7
#define SL_SPIDRV_USART_SPI_DAC_TX_PORT          gpioPortC
#define SL_SPIDRV_USART_SPI_DAC_TX_PIN           7
#define SL_SPIDRV_USART_SPI_DAC_TX_LOC           12

// USART1 RX on PC6
#define SL_SPIDRV_USART_SPI_DAC_RX_PORT          gpioPortC
#define SL_SPIDRV_USART_SPI_DAC_RX_PIN           6
#define SL_SPIDRV_USART_SPI_DAC_RX_LOC           10

// USART1 CLK on PC8
#define SL_SPIDRV_USART_SPI_DAC_CLK_PORT         gpioPortC
#define SL_SPIDRV_USART_SPI_DAC_CLK_PIN          8
#define SL_SPIDRV_USART_SPI_DAC_CLK_LOC          11

// USART1 CS on PC9
#define SL_SPIDRV_USART_SPI_DAC_CS_PORT          gpioPortC
#define SL_SPIDRV_USART_SPI_DAC_CS_PIN           9
#define SL_SPIDRV_USART_SPI_DAC_CS_LOC           11
// [USART_SL_SPIDRV_USART_SPI_DAC]$
// <<< sl:end pin_tool >>>

#endif // SL_SPIDRV_USART_SPI_DAC_CONFIG_H
