/*
 *  peripherals/adc.c
 *
 *  Created on: January 21, 2023
 *      Author: Timothy C. Sweeney-Fanelli
 *              Affects AI
 *              tim@affects.ai
 *
 *  For ADC Reference, see publication AN0021:
 *     https://www.silabs.com/documents/public/application-notes/AN0021.pdf
 *
 *  As well as the EFR32xG1 Reference Manual:
 *     https://www.silabs.com/documents/public/reference-manuals/efr32xg1-rm.pdf
 */

#include "adc.h"
#include <em_cmu.h>

/*
 * ADC Initialization structure -- 256 cycle oversample w/ 2.5V reference, reading
 * differential across the ADC_BAT_POS_SEL and ADC_BAT_NEG_SEL pins.
 */
ADC_InitSingle_TypeDef initSingleBattery  =   {                                   \
    0,                       /* PRS is not used - ignore this value */            \
    adcAcqTime256,           /* 256 ADC_CLK cycle acquisition time. */            \
    adcRef2V5,               /* 2.50 V internal reference. */                     \
    adcResOVS,               /* Oversampling enabled resolution. */               \
    ADC_BAT_POS_SEL,         /* BATT_PWR_MON_HIGH  */                             \
    ADC_BAT_NEG_SEL,         /* BATT_PWR_MON_LOW   */                             \
    false,                   /* Single-ended input. */                            \
    false,                   /* PRS disabled. */                                  \
    false,                   /* Right adjust. */                                  \
    false,                   /* Deactivate conversion after one scan sequence. */ \
    false,                   /* No EM2 DMA wakeup from single FIFO DVL */         \
    false                    /* Discard new data on full FIFO. */                 \
  };

/*
 * ADC Initialization structure -- 256 cycle oversample w/ 2.5V reference, reading
 * differential across the ADC_BAT_POS_SEL and ADC_BAT_NEG_SEL pins.
 */
ADC_InitSingle_TypeDef initSinglePin =   {                                   \
    0,                       /* PRS is not used - ignore this value */            \
    adcAcqTime32,            /* 256 ADC_CLK cycle acquisition time. */            \
    adcRef2V5,               /* 2.50 V internal reference. */                     \
    adcRes12Bit,             /* Oversampling enabled resolution. */               \
    0,
    0,
    true,                    /* Single-ended input. */                            \
    false,                   /* PRS disabled. */                                  \
    false,                   /* Right adjust. */                                  \
    false,                   /* Deactivate conversion after one scan sequence. */ \
    false,                   /* No EM2 DMA wakeup from single FIFO DVL */         \
    false                    /* Discard new data on full FIFO. */                 \
  };

void ADC_initialize(void) {
	// Enable ADC0 clock
	CMU_ClockEnable(cmuClock_ADC0, true);

	// Initialized the ADC
	ADC_Init_TypeDef init = ADC_INIT_DEFAULT;
	init.timebase = ADC_TimebaseCalc(0);
	init.prescale = ADC_PrescaleCalc(ADC_CLOCK, 0);
	init.ovsRateSel = adcOvsRateSel128;

	ADC_reset();
	ADC_Init(ADC0, &init);
}

void ADC_reset() {
  ADC_Reset(ADC0);
}

int32_t ADC_read(const ADC_InitSingle_TypeDef *init) {
  int32_t raw;

  // Initialize and begin an ADC single-sample conversion
  ADC_InitSingle(ADC0, init);
  ADC_Start(ADC0, adcStartSingle);

  // Wait for the read to complete
  while (!(ADC0->STATUS & _ADC_STATUS_SINGLEDV_MASK))
    ;

  // Get the ADC result
  raw = ADC_DataSingleGet(ADC0);
  return raw;
}

int32_t ADC_readPin(uint32_t pin) {
  initSinglePin.posSel = pin;
  return ADC_read(&initSinglePin);
}

int32_t ADC_readPowerMonitor( ) {
  return ADC_read(&initSingleBattery);
}
