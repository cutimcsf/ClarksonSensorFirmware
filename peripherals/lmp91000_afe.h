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
  LMP9100_1 = 1,
  LMP9100_2
} LMP9100_Selector;

void enable_lmp9100(const LMP9100_Selector sel);

#endif

