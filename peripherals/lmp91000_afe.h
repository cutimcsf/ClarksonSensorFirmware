/*
 *  peripherals/lmp91000.c
 *
 *  Created on: January 21, 2023
 *      Author: Timothy C. Sweeney-Fanelli
 *              Affects AI
 *              tim@affects.ai
 *
 *  Methods for interacting with the LMP91000 chips.
 *  https://www.ti.com/lit/ds/symlink/lmp91000.pdf
 ******************************************************************************/

#ifndef LMP91000_H__
#define LMP91000_H__

#include "i2c/i2c_lmp_config.h"

/******************************************************************************
 * Register addresses.
 *****************************************************************************/
#define LMP91000_STATUS_REG_ADDY               0x00u
#define LMP91000_LOCK_REG_ADDY                 0x01u
#define LMP91000_TIACN_REG_ADDY                0x10u
#define LMP91000_REFCN_REG_ADDY                0x11u
#define LMP91000_MODECN_REG_ADDY               0x12u

/******************************************************************************
 * MODE Control Register Values.
 *****************************************************************************/
#define OP_FET_SHORT_DISABLED                 0u
#define OP_FET_SHORT_ENABLED                  1u
#define OP_MODE_DEEP_SLEEP                    0b000u
#define OP_MODE_2_LEAD                        0b001u
#define OP_MODE_STANDBY                       0b010u
#define OP_MODE_3_LEAD                        0b011u
#define OP_MODE_TEMP_MEAS_ON                  0b111u
#define OP_MODE_TEMP_MEAS_OFF                 0b110u

#define GET_OPMODE_VALUE(short_en, mode)      (short_en<<7 & mode)
#define GET_OPMODE_MODE(value)                (value&0b111)
#define GET_OPMODE_SHORT_EN(value)            ((value&0b1000000) >> 7)


/******************************************************************************
 * TIACN Control Register Values.
 *****************************************************************************/
#define TIA_GAIN_EXT   0b000u
#define TIA_GAIN_2_75K 0b001u
#define TIA_GAIN_3_5K  0b010u
#define TIA_GAIN_7K    0b011u
#define TIA_GAIN_14K   0b100u
#define TIA_GAIN_35K   0b101u
#define TIA_GAIN_120K  0b110u
#define TIA_GAIN_350K  0b111u
#define TIA_GAIN_MASK  0b00011100u

#define TIA_RLOAD_10   0b00u
#define TIA_RLOAD_33   0b01u
#define TIA_RLOAD_50   0b10u
#define TIA_RLOAD_100  0b11u
#define TIA_RLOAD_MASK 0b00000011u

#define GET_TIA_REG_VALUE(gain,rload)   (gain<<2&rload)
#define GET_TIA_RLOAD(value)            (value&TIA_RLOAD_MASK)
#define GET_TIA_GAIN(value)             ((value&TIA_GAIN_MASK)>>2)

/******************************************************************************
 * REFCN Control Register Values.
 *****************************************************************************/
#define REFCN_REF_SOURCE_INTERNAL    0u
#define REFCN_REF_SOURCE_EXTERNAL    1u
#define REFCN_REF_SOURCE_MASK        0b10000000u
#define REFCN_REF_SOURCE_SHIFT       0x7u

#define REFCN_INT_Z_20_PCT           0b00u
#define REFCN_INT_Z_50_PCT           0b01u
#define REFCN_INT_Z_67_PCT           0b10u
#define REFCN_INT_Z_0BYPASS          0b11u
#define REFCN_INT_Z_MASK             0b01100000u
#define REFCN_INT_Z_SHIFT            0x5u

#define REFCN_BIAS_SIGN_NEGATIVE     0u
#define REFCN_BIAS_SIGN_POSITIVE     1u
#define REFCN_BIAS_SIGN_MASK         0b00010000u
#define REFCN_BIAS_SIGN_SHIFT        0x4u

#define REFCN_BIAS_MAGNITUDE_1_PCT   0b0001u
#define REFCN_BIAS_MAGNITUDE_2_PCT   0b0010u
#define REFCN_BIAS_MAGNITUDE_4_PCT   0b0011u
#define REFCN_BIAS_MAGNITUDE_6_PCT   0b0100u
#define REFCN_BIAS_MAGNITUDE_8_PCT   0b0101u
#define REFCN_BIAS_MAGNITUDE_10_PCT  0b0110u
#define REFCN_BIAS_MAGNITUDE_12_PCT  0b0111u
#define REFCN_BIAS_MAGNITUDE_14_PCT  0b1000u
#define REFCN_BIAS_MAGNITUDE_16_PCT  0b1001u
#define REFCN_BIAS_MAGNITUDE_18_PCT  0b1010u
#define REFCN_BIAS_MAGNITUDE_20_PCT  0b1011u
#define REFCN_BIAS_MAGNITUDE_22_PCT  0b1100u
#define REFCN_BIAS_MAGNITUDE_24_PCT  0b1101u
#define REFCN_BIAS_MAGNITUDE_MASK    0b00001111u
#define REFCN_BIAS_MAGNITUDE_SHIFT   0x0u

#define GET_REFCN_REG_VALUE(source,int_z,bias_sign,bias) (source<<REFCN_REF_SOURCE_SHIFT & int_z<<REFCN_INT_Z_SHIFT & bias_sign<<REFCN_BIAS_SIGN_SHIFT & bias)
#define GET_REFCN_SOURCE(value)                          ((value&REFCN_REF_SOURCE_MASK)>>REFCN_REF_SOURCE_SHIFT)
#define GET_REFCN_INT_Z(value)                           ((value&REFCN_INT_Z_MASK)>>REFCN_INT_Z_SHIFT)
#define GET_REFCN_BIAS_SIGN(value)                       ((value&REFCN_BIAS_SIGN_MASK)>>REFCN_BIAS_SIGN_SHIFT)
#define GET_REFCN_BIAS_MAGNITUDE(value)                  ((value&REFCN_BIAS_MAGNITUDE_MASK)>>REFCN_BIAS_MAGNITUDE_SHIFT)


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

void LMP91000_setOpMode(uint8_t fetuint8_tEnabled, uint8_t opMode);
void LMP91000_getOpMode(uint8_t *fetuint8_tEnabled, uint8_t *opMode);

void LMP91000_setRefCN(uint8_t source, uint8_t intz, uint8_t sign, uint8_t bias);
void LMP91000_getRefCN(uint8_t *source, uint8_t *intz, uint8_t *sign, uint8_t *bias);

void LMP91000_setTIACN(uint8_t gain, uint8_t rload);
void LMP91000_getTIACN(uint8_t *gain, uint8_t *rload);

void LMP91000_setLock(uint8_t value);
void LMP91000_getLock(uint8_t *value);

void LMP91000_getStatus(uint8_t *value);



#endif

