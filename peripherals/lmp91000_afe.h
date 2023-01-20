/*
 * afe.h
 *
 *  Created on: Jan 20, 2023
 *      Author: Tim Sweeney-Fanelli
 */

#ifndef AFE_H
#define AFE_H

#include <peripherals/i2c/i2c_lmp_config.h>

typedef enum {
  LMP91000_1 = 1,
  LMP91000_2
} LMP91000_Selector;

/******************************************************************************
 * Both LMP91000 sensors are on the same ABUS, but different pins, so we
 * actually have to re-initialize the i2c driver to switch sensors. This was
 * a design error that will be corrected if we make more PCBs.
 *
 * Call this method passing in either LMP91000_1 or LMP91000_2 to set the
 * active sensor.
 *****************************************************************************/
void LMP91000_enableSensor(const LMP91000_Selector sel);

#endif

