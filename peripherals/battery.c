/*
 * Battery.c
 *
 *  Created on: Jun 27, 2020
 *      Author: Timothy C. Fanelli
 *              Zero Byte LLC
 *              hello@zerobytellc.com
 */

#include "adc.h"
#include "battery.h"
#include <sl_bt_api.h>

#define R1				1000000
#define R2				1000000
#define RFACTOR			((R1+R2)/R2)
#define RAW_OFFSET		(ADC_SAMPLE_MAXVAL*10/FULL_MILLIS)

#define FULL_MILLIS		(3350)


#define HISTORY_LEN 5
static uint32_t history[HISTORY_LEN];
static uint8_t  historyIndex = 0;

static void flushHistory(uint32_t powerLevel) {
  CORE_CRITICAL_SECTION(
    for ( int i = 0; i < HISTORY_LEN; ++i )
      history[i] = powerLevel;

    historyIndex = HISTORY_LEN;
  )
}

static void addToHistory(int32_t value) {
  CORE_CRITICAL_SECTION(
    if ( historyIndex == HISTORY_LEN ) {
        for ( int i = 1; i < HISTORY_LEN; ++i ) {
            history[i-1] = history[i];
        }

        historyIndex = HISTORY_LEN-1;
    }

    history[historyIndex++] = value;
  )
}

uint32_t Battery_getCurrentLevel() {
  uint8_t maxidx = 0;
  uint8_t maxcnt = 0;
  uint8_t counts[HISTORY_LEN];
  uint32_t response;

  CORE_CRITICAL_SECTION(
    for ( uint8_t i = 0; i < historyIndex; ++i ) {
        counts[i] = 0;
        for ( uint8_t j = i+1; j < historyIndex; ++j ) {
            if ( history[i] == history[j] ) ++counts[i];
        }
    }

    for ( uint8_t i = 0; i < historyIndex; ++i ) {
        if ( counts[i] > maxcnt ) {
            maxcnt = counts[i];
            maxidx = i;
        }
    }

    response = history[maxidx];
  )

  return response;
}



int Battery_getTrendSlope() {
  int sumy  = 0;
  int sumxy = 0;

  int m = 0;

  CORE_CRITICAL_SECTION(
    const int n = (int) historyIndex;

    if ( n > 1 ) {
      const int sumx = n*(n+1)/2;         // 1+2+...+n = n(n+1)/2
      const int sumx2 = n*(n+1)*(2*n+1)/6;  // https://www.math-only-math.com/sum-of-the-squares-of-first-n-natural-numbers.html
      const int sqr_sumx = sumx*sumx; // sumx^2;

      for ( int i = 1; i <= n; ++i ) {
          sumy += history[i-1];
          sumxy += i * history[i-1];
      }

      int denom = historyIndex * sumx2 - sqr_sumx;
      m = ((int32_t)(historyIndex * sumxy) - (int32_t)(sumx * sumy)) / denom;
    }
  )

  return m;
}

const uint32_t HIGH = 4200;   // 100%
const uint32_t LOW  = 3000;   // 0%

uint32_t Battery_updatePowerLevel(bool flush) {
  uint32_t millivolts;
  uint32_t percentOfSpan;
  int32_t  powerLevel;
  double distanceToZero;
	uint64_t raw = 0;

  GPIO_PinModeSet(gpioPortC, 10, gpioModeInputPull, 0);
  raw = ADC_readPowerMonitor();
  GPIO_PinModeSet(gpioPortC, 10, gpioModeDisabled, 0);

	raw = (raw/10)*10;

	millivolts = raw * FULL_MILLIS / 0x10000;
  millivolts *= 2;

  if ( millivolts > HIGH ) {
    millivolts = HIGH;
  }
  else if ( millivolts < LOW ) {
    millivolts = LOW;
  }

  distanceToZero = (millivolts-LOW);
  percentOfSpan = 100*(distanceToZero/(HIGH-LOW)) - 1;
  powerLevel = percentOfSpan + 5 - percentOfSpan % 5;

  if ( flush )
    flushHistory(powerLevel);
  else
    addToHistory(powerLevel);

  return Battery_getCurrentLevel();
}

