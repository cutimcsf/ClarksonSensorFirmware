/*
 *  peripherals/adc.h
 *
 *  Created on: January 21, 2023
 *      Author: Timothy C. Sweeney-Fanelli
 *              Affects AI
 *              tim@affects.ai
 *
 *  Interface to the onboard ADC0. Used to read the battery power monitor pins.
 ******************************************************************************/

#ifndef ADC_H__
#define ADC_H__

#include "em_adc.h"

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
int32_t ADC_readPowerMonitor( );

/******************************************************************************
 * ADC_reset()
 * Resets the ADC. Serves no practical purpose at the moment...
 *****************************************************************************/
void ADC_reset();

#endif
