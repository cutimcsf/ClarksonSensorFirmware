#ifndef PIN_CONFIG_H
#define PIN_CONFIG_H

// $[ACMP0]
// [ACMP0]$

// $[ACMP1]
// [ACMP1]$

// $[ADC0]
// [ADC0]$

// $[CMU]
// [CMU]$

// $[DBG]
// DBG SWCLKTCK on PF0
#define DBG_SWCLKTCK_PORT                        gpioPortF
#define DBG_SWCLKTCK_PIN                         0
#define DBG_ROUTE_LOC                            0

// DBG SWDIOTMS on PF1
#define DBG_SWDIOTMS_PORT                        gpioPortF
#define DBG_SWDIOTMS_PIN                         1

// DBG TDO on PF2
#define DBG_TDO_PORT                             gpioPortF
#define DBG_TDO_PIN                              2

// [DBG]$

// $[ETM]
// [ETM]$

// $[PTI]
// [PTI]$

// $[GPIO]
// [GPIO]$

// $[I2C0]
// I2C0 SCL on PB12
#define I2C0_SCL_PORT                            gpioPortB
#define I2C0_SCL_PIN                             12
#define I2C0_SCL_LOC                             6

// I2C0 SDA on PB11
#define I2C0_SDA_PORT                            gpioPortB
#define I2C0_SDA_PIN                             11
#define I2C0_SDA_LOC                             6

// [I2C0]$

// $[I2C1]
// [I2C1]$

// $[LESENSE]
// [LESENSE]$

// $[LETIMER0]
// [LETIMER0]$

// $[LEUART0]
// [LEUART0]$

// $[LFXO]
// [LFXO]$

// $[MODEM]
// [MODEM]$

// $[PCNT0]
// [PCNT0]$

// $[PCNT1]
// [PCNT1]$

// $[PCNT2]
// [PCNT2]$

// $[PRS.CH0]
// [PRS.CH0]$

// $[PRS.CH1]
// [PRS.CH1]$

// $[PRS.CH2]
// [PRS.CH2]$

// $[PRS.CH3]
// [PRS.CH3]$

// $[PRS.CH4]
// [PRS.CH4]$

// $[PRS.CH5]
// [PRS.CH5]$

// $[PRS.CH6]
// [PRS.CH6]$

// $[PRS.CH7]
// [PRS.CH7]$

// $[PRS.CH8]
// [PRS.CH8]$

// $[PRS.CH9]
// [PRS.CH9]$

// $[PRS.CH10]
// [PRS.CH10]$

// $[PRS.CH11]
// [PRS.CH11]$

// $[TIMER0]
// [TIMER0]$

// $[TIMER1]
// [TIMER1]$

// $[USART0]
// USART0 CLK on PF7
#define USART0_CLK_PORT                          gpioPortF
#define USART0_CLK_PIN                           7
#define USART0_CLK_LOC                           29

// USART0 CS on PF4
#define USART0_CS_PORT                           gpioPortF
#define USART0_CS_PIN                            4
#define USART0_CS_LOC                            25

// USART0 RX on PF5
#define USART0_RX_PORT                           gpioPortF
#define USART0_RX_PIN                            5
#define USART0_RX_LOC                            28

// USART0 TX on PF6
#define USART0_TX_PORT                           gpioPortF
#define USART0_TX_PIN                            6
#define USART0_TX_LOC                            30

// [USART0]$

// $[USART1]
// USART1 CLK on PC8
#define USART1_CLK_PORT                          gpioPortC
#define USART1_CLK_PIN                           8
#define USART1_CLK_LOC                           11

// USART1 CS on PC9
#define USART1_CS_PORT                           gpioPortC
#define USART1_CS_PIN                            9
#define USART1_CS_LOC                            11

// USART1 RX on PC6
#define USART1_RX_PORT                           gpioPortC
#define USART1_RX_PIN                            6
#define USART1_RX_LOC                            10

// USART1 TX on PC7
#define USART1_TX_PORT                           gpioPortC
#define USART1_TX_PIN                            7
#define USART1_TX_LOC                            12

// [USART1]$

// $[USART2]
// [USART2]$

// $[USART3]
// [USART3]$

// $[VDAC0]
// [VDAC0]$

// $[WTIMER0]
// [WTIMER0]$

// $[WTIMER1]
// [WTIMER1]$

// $[CUSTOM_PIN_NAME]
#define LMP2_SDA_PORT                            gpioPortA
#define LMP2_SDA_PIN                             0

#define LMP2_SCL_PORT                            gpioPortA
#define LMP2_SCL_PIN                             1

#define LMP2_ENLOW_PORT                          gpioPortA
#define LMP2_ENLOW_PIN                           2

#define LMP2_TEMP_PORT                           gpioPortA
#define LMP2_TEMP_PIN                            3

#define LMP1_TEMP_PORT                           gpioPortA
#define LMP1_TEMP_PIN                            5

#define LMP1_SDA_PORT                            gpioPortB
#define LMP1_SDA_PIN                             11

#define LMP1_SCL_PORT                            gpioPortB
#define LMP1_SCL_PIN                             12

#define LMP1_ENLOW_PORT                          gpioPortB
#define LMP1_ENLOW_PIN                           13

#define DAC_3W_SPI_SDIO1_PORT                    gpioPortC
#define DAC_3W_SPI_SDIO1_PIN                     6

#define DAC_3W_SPI_SDIO2_PORT                    gpioPortC
#define DAC_3W_SPI_SDIO2_PIN                     7

#define DAC_3W_SPI_SCLK_PORT                     gpioPortC
#define DAC_3W_SPI_SCLK_PIN                      8

#define DAC_ENLOW_PORT                           gpioPortC
#define DAC_ENLOW_PIN                            9

#define BATT_PWR_MON_HIGH_PORT                   gpioPortD
#define BATT_PWR_MON_HIGH_PIN                    13

#define BATT_PWR_MON_LOW_PORT                    gpioPortD
#define BATT_PWR_MON_LOW_PIN                     14

#define ACC_ENLOW_PORT                           gpioPortF
#define ACC_ENLOW_PIN                            4

#define ACC_SPI_MISO_PORT                        gpioPortF
#define ACC_SPI_MISO_PIN                         5

#define ACC_SPI_MOSI_PORT                        gpioPortF
#define ACC_SPI_MOSI_PIN                         6

#define ACC_SPI_CLK_PORT                         gpioPortF
#define ACC_SPI_CLK_PIN                          7

// [CUSTOM_PIN_NAME]$

#endif // PIN_CONFIG_H

