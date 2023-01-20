/*
 * ADC.c
 *
 *  Created on: Jun 27, 2020
 *      Author: Timothy C. Fanelli
 *              Zero Byte LLC
 *              hello@zerobytellc.com
 *
 *  Interface to the onboard ADC0. We use 1.25V internal reference voltage, with
 *  an oversample rate of 4096 resulting in 16- bit resolution. These values
 *  are hard-coded into the implementation right now, but this can be made
 *  more generic in the future if necessary.
 ******************************************************************************/

#ifndef ADC_H__
#define ADC_H__

#include "em_adc.h"
#include "em_cmu.h"

#define ADC_BAT_POS_SEL			adcPosSelAPORT4XCH29		/* PB13							*/
#define ADC_BAT_NEG_SEL			adcNegSelAPORT2YCH10		/* PC10							*/
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
uint32_t ADC_readPowerMonitor( );

/******************************************************************************
 * ADC_reset()
 * Resets the ADC. Serves no practical purpose at the moment...
 *****************************************************************************/
void ADC_reset();

#endif
