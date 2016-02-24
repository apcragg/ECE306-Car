//============================================================================//
// File Name : timer_interrupts.c
//
// Description: This file contains the timer ISR code
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//============================================================================//

#include "msp430.h"
#include "macros.h"
#include "timers.h"

//------------------------------------------------------------------------------
// Interrupt Name : timer_A0_CCR0_interupt
//
// Description: This ISR services the Timer A0 interrupt which indicates 5ms
//              have past. Updates the timer_count varriable. Resets the 
//              interrupt flag.
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
#pragma vector = TIMER0_A0_VECTOR
__interrupt void timer_A0_CCR0_interupt(void)
{
  increment_timer_count();
  TA0CCTL0 &= ~TAxCTL_IFG;        // clears the interupt flag
}

//------------------------------------------------------------------------------
// Interrupt Name : timer_B1_CCR0_interupt
//
// Description: This ISR services the Timer B1 overflow interrupt and 
//              simply clears the interrupt flags.
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
#pragma vector = TIMER1_B1_VECTOR
__interrupt void timer_B1_CCR0_interupt(void)
{
  TB1CCTL1 &= ~TAxCTL_IFG;        // clears the interupt flag
  TB1CCTL2 &= ~TAxCTL_IFG;        // clears the interupt flag
}

//------------------------------------------------------------------------------
// Interrupt Name : timer_B2_CCR0_interupt
//
// Description: This ISR services the Timer B2 overflow interrupt and 
//              simply clears the interrupt flags.
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
#pragma vector = TIMER2_B1_VECTOR
__interrupt void timer_B2_CCR0_interupt(void)
{
  TB2CCTL1 &= ~TAxCTL_IFG;        // clears the interupt flag
  TB2CCTL2 &= ~TAxCTL_IFG;        // clears the interupt flag
}

//------------------------------------------------------------------------------
// Interrupt Name : timer_A1_CCR1_interupt
//
// Description: This ISR services the Timer A1 CCR1 compare mode interrupt 
//              that is used for debouncing the on board switches. It 
//              reenables the port interrupts after the debounce time is up
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
#pragma vector = TIMER1_A1_VECTOR
__interrupt void timer_A1_CCR1_interupt(void)
{
  TA1CCTL1 &= ~CCIFG;             // clears the interupt flag
  TA1CCTL1 &= ~CCIE;
  P4IE |= SW_1 | SW_2; 
}

//------------------------------------------------------------------------------
// Interrupt Name : timer_A1_CTL_interupt
//
// Description: This ISR services the Timer A1 overflow interrupt and clears
//              the flags.
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
#pragma vector = TIMER1_A0_VECTOR
__interrupt void timer_A1_CTL_interupt(void)
{
  TA1CTL &= ~CCIFG;             // clears the interupt flag
}