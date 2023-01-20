/*
 * Battery.h
 *
 *  Created on: Jun 27, 2020
 *      Author: Timothy C. Fanelli
 *              Zero Byte LLC
 *              hello@zerobytellc.com
 */

#ifndef BCI_INTERFACES_H_
#define BCI_INTERFACES_H_

#include "sl_bt_types.h"

//////////////////////
// BATTERY
/////////////////////////
uint32_t Battery_updatePowerLevel(uint8_t flush);
uint32_t Battery_getCurrentLevel();
int Battery_getTrendSlope();

#endif /* BCI_INTERFACES_H_ */
