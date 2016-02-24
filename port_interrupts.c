//============================================================================//
// File Name : port_interrupts.c
//
// Description: This file contains the port ISR code
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//============================================================================//

#include "msp430.h"
#include "macros.h"
#include "switch.h"

//------------------------------------------------------------------------------
// Interrupt Name : SW_PRESSED_ISR
//
// Description: This ISR services the Port 4 interrupts related to the two on
//              board switches. It determines which switch was pressed using the
//              TxxIV register and disables interrupts on that port pin for
//              debouncing. It then switches the edge mode for the interrupt
//              to receive the rising/falling edge of the next button press/
//              release. It enables the TA1CCR1 compare register to count a
//              specified debounce time before that ISR renenables interrupts.
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
#pragma vector = PORT4_VECTOR
__interrupt void SW_PRESSED_ISR(void)
{
  u_int8 current_ifg = P4IV >> OFF_BY_ONE_OFFSET; // Shifts port interrupt label
                                                  // format used by SW_1 / SW_2
  
  P4IE &= ~(current_ifg);                         // Port interrupts turned off
  
  if((P4IES & current_ifg)) 
  {
    P4IES &= ~current_ifg;                        // Toggle rising/falling edge
    sw_pressed(current_ifg);
  }
  else
  {
    P4IES |= current_ifg;                         // Toggle rising/falling edge
    sw_released(current_ifg);
  }

  unsigned int temp_edge = P4IES;
  TA1CCR1 = (TA1R + ((TA1_CLK_F / ONE_MSEC) *
            (temp_edge & current_ifg ? PRESSED_DEBOUNCE : RELEASED_DEBOUNCE))) 
            % UINT_16_MAX;
  
  TA1CCTL1 &= ~CCIFG;
  TA1CCTL1 |= CCIE;

  P4IFG &= ~current_ifg;                
}
