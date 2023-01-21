/*
 *  peripherals/lmp91000.c
 *
 *  Created on: January 21, 2023
 *      Author: Timothy C. Sweeney-Fanelli
 *              Affects AI
 *              tim@affects.ai
 *
 *  Methods for interacting with the LMP91000 chips.
 ******************************************************************************/

#ifndef LMP91000_H__
#define LMP91000_H__

#include "i2c/i2c_lmp_config.h"

/******************************************************************************
 * Selector values to choose between the LMP1 and LMP2 chips on the PCB.
 *****************************************************************************/
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

