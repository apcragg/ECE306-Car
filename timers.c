//============================================================================//
// File Name : timers.c
//
// Description: This file contains the timer intialization and delay code.
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//============================================================================//

#include "timers.h"

//------------------------------------------------------------------------------
// Function Name : five_msec_delay
//
// Description: This function calls a delay for a 5ms multiple of the passed
//              delay arguement.
// Arguements: unsigned int     delay
// Returns:    void
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void five_msec_delay(unsigned int delay)
{
  unsigned int end_count = timer_count + delay;
  
  while(timer_count < end_count);
}

//------------------------------------------------------------------------------
// Function Name : init_timers
//
// Description: This function calls the individual timer intialization 
//              functions.
// Arguements: void
// Returns:    void
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void init_timers()
{
  init_timer_A0();
}

 //------------------------------------------------------------------------------
// Function Name : init_timer_A0
//
// Description: This function initializes the timer A0. This sets up the global
//              timer used in the program's functions. It is set up as an 8Mhz 
//              clock with a CCR1 register calling an ISR to increment a time
//              value every 5ms.
// Arguements: void
// Returns:    void
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void init_timer_A0()
{
  TA0CTL = CLEAR_REGISTER;
  
  TA0CTL |= TASSEL__SMCLK;
  TA0CTL |= MC__UP;
  
  TA0CCTL0 = CLEAR_REGISTER;
  
  TA0CCTL0 |= CCIE;
  
  TA0CCR0 = TA0_FREQ;
}

//------------------------------------------------------------------------------
// Function Name : get_timer_count
//
// Description: This function returns the timer_count varriable 
//              functions.
// Arguements: void
// Returns:    timer_count
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
unsigned int get_timer_count()
{
  return timer_count;
}

//------------------------------------------------------------------------------
// Function Name : increment_timer_count
//
// Description: This function increments the timer_count varriable.
// Arguements: void
// Returns:    void
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void increment_timer_count()
{
  timer_count++;
}