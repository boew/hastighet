#include "LPC_Timer.h"

int boe_TimerCaptureInit (LPC_SysControl_ExtInt_Channel_t ExtIntNum,
                          bool WakeupEnable)
{
  switch(ExtIntNum)
  {
  case EXTINT0:
    // Assign pin to Ext Interrupt logic
    PINSEL1_bit.P0_16 = 1;
    // Clear interrupt flag
    EXTINT_bit.EINT0 = 1;
    // Set Wake-up
    if (WakeupEnable)
      EXTWAKE_bit.EXTWAKE0 = 1;
    else
      EXTWAKE_bit.EXTWAKE0 = 0;
    break;
  case EXTINT1:
    // Assign pin to Ext Interrupt logic
    PINSEL0_bit.P0_14 = 1;
    // Clear interrupt flag
    EXTINT_bit.EINT1 = 1;
    // Set Wake-up
    if (WakeupEnable)
      EXTWAKE_bit.EXTWAKE1 = 1;
    else
      EXTWAKE_bit.EXTWAKE1 = 0;
    break;
  case EXTINT2:
    // Assign pin to Ext Interrupt logic
    PINSEL0_bit.P0_15 = 1;
    // Clear interrupt flag
    EXTINT_bit.EINT2 = 1;
    // Set Wake-up
    if (WakeupEnable)
      EXTWAKE_bit.EXTWAKE2 = 1;
    else
      EXTWAKE_bit.EXTWAKE2 = 0;
    break;
  default:
    return 1;
  }
  return 0;
}
