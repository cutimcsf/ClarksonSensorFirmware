/*
 *  peripherals/battery.h
 *
 *  Created on: January 21, 2023
 *      Author: Timothy C. Sweeney-Fanelli
 *              Affects AI
 *              tim@affects.ai
 *
 *  Methods for obtaining battery level and related info.
 ******************************************************************************/


#ifndef BATTERY_H__
#define BATTERY_H__

#include <sl_bt_types.h>

#define HISTORY_LEN 5

/******************************************************************************
 * Reads the current battery level using the microcontroller's built-in ADC.
 * Battery level is returned in millivolts. This method does NOT update the
 * history.
 *
 * @return The current battery level in millivolts
 *****************************************************************************/
uint32_t Battery_readCurrentMillis();

/******************************************************************************
 * Reads the current battery level using the microcontroller's built-in ADC.
 * Battery level is rounded to the nearest 5%, and added to a history buffer.
 *
 * @return The current battery level rounded to the nearest 5%
 *****************************************************************************/
uint32_t Battery_readCurrentPowerLevel();

/******************************************************************************
 * Reads the current battery level using the microcontroller's built-in ADC.
 * Battery level is rounded to the nearest 5%. The history buffer is flushed
 * using this new value.
 *
 * @return The current battery level rounded to the nearest 5%
 *****************************************************************************/
uint32_t Battery_readAndFlushCurrentPowerLevel();

/******************************************************************************
 * Returns the current battery level from memory, but does not read the ADC to
 * update the value. Value returned is the median of up-to the last HISTORY_LEN
 * calls to Battery_readCurrentPowerLevel()
 *
 * @return The median powerlevel over the last several values.
 *****************************************************************************/
uint32_t Battery_getCurrentLevel();

/******************************************************************************
 * Determines if the battery is charging or discharging based on the last
 * several battery readings. Positive value indicates charging, negative indicates
 * discharging, and zero indicates stable. IF - and ONLY IF - you call
 * Battery_readCurrentPowerLevel at a fixed interval, then the value returned
 * here can also be used to infer rate of discharge or rate of charge for the
 * battery.
 *
 * @return The slope of the linear best-fit line drawn through the history
 *          values.
 *****************************************************************************/
int Battery_getTrendSlope();

#endif
