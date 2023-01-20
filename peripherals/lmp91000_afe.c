#include <peripherals/lmp91000_afe.h>
#include "app_assert.h"

void LMP91000_enableSensor(const LMP91000_Selector sel) {
  I2CSPM_Init_TypeDef *lmp_init;
  switch( sel ) {
    case LMP91000_1:
      lmp_init = &init_lmp1;
      break;

    case LMP91000_2:
      lmp_init = &init_lmp2;
      break;

    default:
      app_assert(false, "Invalid LMP9100_Selector value. Unable to proceed.");
      break;
  }

  CMU_ClockEnable(cmuClock_GPIO, true);
  I2CSPM_Init(lmp_init);
}

