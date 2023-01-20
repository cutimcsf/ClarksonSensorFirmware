/*
 * Battery.h
 *
 *  Created on: Jun 27, 2020
 *      Author: Timothy C. Fanelli
 *              Zero Byte LLC
 *              hello@zerobytellc.com
 */

#ifndef BATTERY_H__
#define BATTERY_H__

#include "sl_bt_types.h"

/******************************************************************************
 * Reads the current battery level using the microcontroller's built-in ADC
 *
 * @param flush
 * @return
 *****************************************************************************/
uint32_t Battery_updatePowerLevel(bool flush);

/******************************************************************************
 * Returns the current battery level from memory, but does not read the ADC to
 * update the value.
 * @return
 *****************************************************************************/
uint32_t Battery_getCurrentLevel();

/******************************************************************************
 * Determines if the battery is charging or discharging based on the last
 * several battery readings.
 *
 * @return
 *****************************************************************************/
int Battery_getTrendSlope();

#endif
