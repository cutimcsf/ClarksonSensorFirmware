/*
 *  peripherals/adc.h
 *
 *  Created on: January 21, 2023
 *      Author: Timothy C. Sweeney-Fanelli
 *              Affects AI
 *              tim@affects.ai
 *
 *  Interface to the onboard ADC0. Used to read the battery power monitor pins.
 *  https://www.silabs.com/documents/public/data-sheets/efr32bg12-datasheet.pdf
 ******************************************************************************/

#ifndef ADC_H__
#define ADC_H__

#include "em_adc.h"


/******************************************************************************
 * ADC pins ... see data sheet (link in header) page 195, ACMP0 Bus and Pin
 * Mapping...
 *****************************************************************************/
#define ADC_BAT_POS_SEL			adcPosSelAPORT4XCH29		/* PB13							*/
#define ADC_BAT_NEG_SEL			adcNegSelAPORT2YCH10		/* PC10							*/
#define LMP91000_1_DATA_PIN  adcPosSelAPORT4XCH13    /* PA5 */
#define LMP91000_2_DATA_PIN  adcPosSelAPORT4XCH11    /* PA5 */

#define ADC_CLOCK           16000000                /* ADC conversion clock     */


/******************************************************************************
 * ADC_initialize() - call once at boot.
 * Do not invoke initializeADC() multiple times.
 *****************************************************************************/
void ADC_initialize();

/******************************************************************************
 * ADC_readPowerMonitor()
 * Reads the ADC to determine voltage across ADC_BAT_POS_SEL and ADC_BAT_NEG_SEL
 * pins.
 *****************************************************************************/
int32_t ADC_readPowerMonitor();

/******************************************************************************
 * ADC_readPin()
 * Reads the ADC to determine voltage across ADC_BAT_POS_SEL and ADC_BAT_NEG_SEL
 * pins.
 *****************************************************************************/
int32_t ADC_readPin(uint32_t pin);

/******************************************************************************
 * ADC_reset()
 * Resets the ADC. Serves no practical purpose at the moment...
 *****************************************************************************/
void ADC_reset();

#endif
