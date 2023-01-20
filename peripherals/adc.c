/*
 * ADC.c
 *
 *  Created on: Jun 27, 2020
 *      Author: Timothy C. Fanelli
 *              Zero Byte LLC
 *              hello@zerobytellc.com
 *
 *  For ADC Reference, see publication AN0021:
 *     https://www.silabs.com/documents/public/application-notes/AN0021.pdf
 *
 *  As well as the EFR32xG1 Reference Manual:
 *     https://www.silabs.com/documents/public/reference-manuals/efr32xg1-rm.pdf
 *
 *  The ADC supports offset and gain calibration to correct errors due to process and
 *  temperature variations. This must be done individual- ly for each reference used.
 *  For each reference, it needs to be repeated for single-ended, negative single-ended
 *  (see 24.3.7 Input Se- lection for details) and differential measurement. The ADC
 *  calibration (ADCn_CAL) register contains register fields for calibrating offset and
 *  gain for both single and scan mode. The gain and offset calibration are done in
 *  single channel mode, but the resulting calibration values can be used for both single
 *  and scan mode.
 *
 *  Gain and offset for various references and modes are calibrated during production and
 *  the calibration values for these can be found in the Device Information page. During
 *  reset, the gain and offset calibration registers are loaded with the production calibration
 *  values for the 1V25 reference. Others can be loaded as needed or the user can perform
 *  calibration on the fly using the particular reference and mode to be used and write the
 *  result in the ADCn_CAL before starting the ADC conversion with them.
 */

#include "adc.h"

ADC_Init_TypeDef init;

ADC_InitSingle_TypeDef initSingleBattery  =   {                                   \
    adcPRSSELCh0,            /* PRS ch0 (if enabled). */                          \
    adcAcqTime256,           /* 256 ADC_CLK cycle acquisition time. */            \
    adcRef2V5,               /* 2.50 V internal reference. */                     \
    ADC_SAMPLE_RESOLUTION,   /* 16 bit resolution. */                             \
    ADC_BAT_POS_SEL,         /* Select node BUS0XCH0 as posSel */                 \
    adcNegSelVSS,            /* Select VSS as negSel */                           \
    false,                   /* Single-ended input. */                            \
    false,                   /* PRS disabled. */                                  \
    false,                   /* Right adjust. */                                  \
    false,                   /* Deactivate conversion after one scan sequence. */ \
    false,                   /* No EM2 DMA wakeup from single FIFO DVL */         \
    false                    /* Discard new data on full FIFO. */                 \
  };

void initializeADC(void) {
	// Enable ADC0 clock
	CMU_ClockEnable(cmuClock_ADC0, true);
	/* Reset ADC to be sure we have default settings and wait for ongoing */
	/* conversions to be complete. */

	ADC_Init_TypeDef init = ADC_INIT_DEFAULT;
	init.timebase = ADC_TimebaseCalc(0);
	init.prescale = ADC_PrescaleCalc(ADC_CLOCK, 0);
	init.ovsRateSel = adcOvsRateSel128;

	resetADC();
	ADC_Init(ADC0, &init);
}

void resetADC() {
  ADC_Reset(ADC0);
}

uint32_t readADC(const ADC_InitSingle_TypeDef *init) {
  int32_t raw;

  ADC_InitSingle(ADC0, init);
  ADC_Start(ADC0, adcStartSingle);

  while (!(ADC0->STATUS & _ADC_STATUS_SINGLEDV_MASK))
    ;

  raw = ADC_DataSingleGet(ADC0);

  if ( raw < 0 )
    raw = 0;

  return (uint32_t) raw;
}

uint32_t readADC_Battery( ) {
  return readADC(&initSingleBattery);
}
