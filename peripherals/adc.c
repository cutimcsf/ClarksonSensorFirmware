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
#include <em_device.h>
#include <em_system.h>

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
    adcAcqTime64,            /* 256 ADC_CLK cycle acquisition time. */            \
    adcRef2V5,                                                                    \
    adcRes12Bit,             /* Oversampling enabled resolution. */               \
    0,
    0,
    false,                    /* Single-ended input. */                            \
    false,                   /* PRS disabled. */                                  \
    false,                   /* Right adjust. */                                  \
    false,                   /* Deactivate conversion after one scan sequence. */ \
    false,                   /* No EM2 DMA wakeup from single FIFO DVL */         \
    false                    /* Discard new data on full FIFO. */                 \
  };

//static uint32_t calibrateADCforReference(ADC_TypeDef *adc, ADC_Ref_TypeDef ref) {
//  uint32_t calreg = DEVINFO->ADC0CAL0;
//  uint8_t gain2v5 = (calreg & 0x7F000000) >> 24;
//  uint8_t negoffset2v5 = (calreg & 0x00F00000) >> 20;
//  uint8_t offset2v5 = (calreg & 0x000F0000) >> 16;
//
//  uint32_t cal = adc->CAL & ~(_ADC_CAL_SINGLEGAIN_MASK | _ADC_CAL_SCANGAIN_MASK | _ADC_CAL_SINGLEOFFSET_MASK | _ADC_CAL_SCANOFFSET_MASK);
//  cal        |= gain2v5 << _ADC_CAL_SINGLEGAIN_SHIFT;
//  cal        |= gain2v5 << _ADC_CAL_SCANGAIN_SHIFT;
//  cal        |= (offset2v5) << _ADC_CAL_SINGLEOFFSET_SHIFT;
//  cal        |= (offset2v5) << _ADC_CAL_SCANOFFSET_SHIFT;
//
//  adc->CAL = cal;
//  return 0;
//}

void ADC_initialize(void) {
	CMU_ClockEnable(cmuClock_ADC0, true);

	ADC_Reset(ADC0);
  ADC_Init_TypeDef init = ADC_INIT_DEFAULT;
  init.timebase = ADC_TimebaseCalc(0);
  init.prescale = ADC_PrescaleCalc(ADC_CLOCK, 0);
  init.ovsRateSel = adcOvsRateSel4096;
  ADC_Init(ADC0, &init);
}

void ADC_reset() {
  ADC_Reset(ADC0);
}

int16_t ADC_read(const ADC_InitSingle_TypeDef *init) {
  int16_t raw;

  // Initialize and begin an ADC single-sample conversion
  ADC_InitSingle(ADC0, init);
  ADC_Start(ADC0, adcStartSingle);

  // Wait for the read to complete
  while (!(ADC0->STATUS & _ADC_STATUS_SINGLEDV_MASK))
    ;

  // Get the ADC result
  raw = (int16_t) ADC_DataSingleGet(ADC0);
  return raw;
}

int16_t ADC_readPin(ADC_PosSel_TypeDef pin) {
  initSinglePin.posSel = pin;
  return ADC_read(&initSinglePin) & 0x0FFE;
}

int32_t ADC_readPowerMonitor( ) {
  return ADC_read(&initSingleBattery);
}
