//============================================================================//
// File Name : timers.c
//
// Description: This file contains the timer information and control functions
//
// Author: Jim Carlson
// Date: Jan 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//============================================================================//


#include "macros.h"
#include "globals.h"
#include "functions.h"

//------------------------------------------------------------------------------
// Function Declarations
    void Init_Timers(void);
    void five_msec_sleep(unsigned int);
    void Timer_code(void);
//------------------------------------------------------------------------------

    
//------------------------------------------------------------------------------
// Function Name : Init_Timers
//
// Description: This function initializes the timers on the MSP430
// Arguements: void
// Returns:    void
//
// Author: Jim Carlson
// Date: Jan 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void Init_Timers(void){
//------------------------------------------------------------------------------
// Timer Configurations
//------------------------------------------------------------------------------
  Init_Timer_A0(); //
//  Init_Timer_A1(); // 
//  Init_Timer_B0(); // 
//  Init_Timer_B1(); //  
//  Init_Timer_B2();   //  Required for provided compiled code to work
//------------------------------------------------------------------------------
}

//------------------------------------------------------------------------------
// Function Name : five_msec_sleep
//
// Description: This function sleeps for (5 milliseconds * fivemsec)
//              using the timer and a counter
// Arguements: unsigned int fivemsec
// Returns:    void
//
// Author: Jim Carlson
// Date: Jan 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void five_msec_sleep(unsigned int fivemsec){
//------------------------------------------------------------------------------
//Each count passed is at least x times 5 milliseconds
  five_msec_count = START_VAL;
  while(fivemsec > (five_msec_count + OFF_BY_ONE_OFFSET));
//------------------------------------------------------------------------------
}

//------------------------------------------------------------------------------
// Function Name : Timer_code
//
// Description: This function increments the Time_Sequence variable and the
//              five_msec_count variable every 5 milliseconds
// Arguements: void
// Returns:    void
//
// Author: Jim Carlson
// Date: Jan 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void Timer_code(void){
//------------------------------------------------------------------------------
// Timer A0 interrupt code
//------------------------------------------------------------------------------
  Time_Sequence++;
  one_time = TRUE;
  if (five_msec_count < TIMER_COUNT){
    five_msec_count++;
  }
//------------------------------------------------------------------------------
}
