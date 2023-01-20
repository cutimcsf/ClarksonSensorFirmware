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

/********************************************************************************************/
/* ADC Calibration Parameters																*/
/********************************************************************************************/
#define ADC_CAL_ACQTIME			adcAcqTime16				/* 16 cycles for calibration 	*/
#define ADC_CAL_OFFSET_VALUE	0xF800						/* ADC offset calibration value */
															/* 0x0000 if single-wire 		*/
															/* 0xF800 if differential		*/
#define ADC_CAL_GAIN_VALUE      0xFFFF         				/* ADC gain calibration value 	*/
#define ADC_CAL_INPUT           adcPosSelAPORT3XCH8     	/* PA0 							*/

/********************************************************************************************/
/* ADC Parameters 												*/
/********************************************************************************************/
#define ADC_CLOCK               16000000                 	/* ADC conversion clock 		*/
#define ADC_ACQ_TIME			adcAcqTime256				/* 256 cycle acq time			*/

/********************************************************************************************/
/* ADC Parameters for battery monitor														*/
/********************************************************************************************/
#define ADC_BAT_REFERENCE		adcRef2V5					/* 2.5V internal reference		*/
#define ADC_BAT_REF_MILLIS		2500						/* 2500 millivolts				*/
#define ADC_BAT_POS_SEL			adcPosSelAPORT4XCH29		/* PB13							*/
#define ADC_BAT_NEG_SEL			adcNegSelAPORT2YCH10		/* PC10							*/

/********************************************************************************************/
/* ADC Samping Parameters																	*/
/* 																							*/
/* adcResOVS is set on the ADC_Init structure to tell the ADC to use oversampling			*/
/* adcOvsRateSel32 is a 16-bit sample with no shifts										*/
/* 0xFFFF is the maximum value that can be returned from a sample - must match the			*/
/*        oversample rate																	*/
/********************************************************************************************/
#define ADC_SAMPLE_RESOLUTION	adcResOVS					    /* Use oversample				*/
#define ADC_OVERSAMPLE_RATE		adcOvsRateSel32				/* 16-bit no shift 				*/
#define ADC_SAMPLE_MAXVAL		  0xFFFF						    /* 16-bit maximum value			*/

/******************************************************************************
 * initializeADC()
 *
 * Use this method to initialize the onboard ADC0 at system boot. Initialization
 * will perform a calibration, and there is no need to calibrate again... but if
 * you want to recalibrate, call calibrateADC() directly -- do not invoke
 * initializeADC() multiple times.
 */
void initializeADC();

uint32_t readADC_Battery( );
uint32_t readADCForBattery();

void resetADC();

#endif
