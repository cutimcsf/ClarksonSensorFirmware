#include <peripherals/lmp91000_afe.h>
#include "app_assert.h"

void enable_lmp9100(const LMP9100_Selector sel) {
  I2CSPM_Init_TypeDef *lmp_init;
  switch( sel ) {
    case LMP9100_1:
      lmp_init = &init_lmp1;
      break;

    case LMP9100_2:
      lmp_init = &init_lmp2;
      break;

    default:
      app_assert(false, "Invalid LMP9100_Selector value. Unable to proceed.");
      break;
  }

  CMU_ClockEnable(cmuClock_GPIO, true);
  I2CSPM_Init(lmp_init);
}

