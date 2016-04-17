//============================================================================//
// File Name : switch.c
//
// Description: This file contains the board control switch functions
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//============================================================================//

#include "switch.h"
#include "adc.h"

    
//------------------------------------------------------------------------------
// Module Scope Globals
    static volatile u_int8 sw_pressed_mask = FALSE;
    static volatile u_int8 sw_down_mask = FALSE;
    
    static volatile u_int8 pressed_count = 0;
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Function Name : Switches_Process
//
// Description: This function polls the current states of Switches SW1/SW2
//              and sets the two different text options based on the switch
//              currently toggled
// Arguements: void
// Returns:    void
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void update_switches()
{
  u_int8 temp_down = sw_down_mask;
  u_int8 temp_pressed = sw_pressed_mask;
  
  menu_handle_input(temp_pressed);  
                                        // Pressed only lasts one cycle
                                        // Down lasts until released
  sw_pressed_mask ^= temp_pressed;
 
  //if(temp_pressed & SW_1)
  //  handle_input(temp_pressed, pressed_count);
}

//------------------------------------------------------------------------------
// Function Name : software_debounce
//
// Description: This function takes a port and pin as inputs and returns the 
//              software debounced state of the requested pin as a bool
// Arguements: unsigned short volatile* port
//             u_int8                   pin_mask
// Returns:    bool                     value
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
bool software_debounce(unsigned short volatile* port, u_int8 pin_mask)
{
  return false;
}

//------------------------------------------------------------------------------
// Function Name : sw_pressed
//
// Description: This function sets the sw_pressed_mask bit for the corresponding
//              bit to which switch was pressed
// Arguements: u_int8 sw_mask
// Returns:    void
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void sw_pressed(u_int8 sw_mask)
{
  sw_pressed_mask |= sw_mask;
  sw_down_mask |= sw_mask;
}     

//------------------------------------------------------------------------------
// Function Name : sw_released
//
// Description: This function clears the sw_pressed_mask bit for the 
//              corresponding bit to which switch was released
// Arguements: u_int8 sw_mask
// Returns:    void                  
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void sw_released(u_int8 sw_mask)
{
  sw_down_mask &= ~sw_mask; 
}

//------------------------------------------------------------------------------
// Function Name : setup_sw_debounce
//
// Description: This sets up switch debouncing and the corresponding
//              port interrupt registers
// Arguements: void
// Returns:    void                  
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void setup_sw_debounce(void)
{
  P4IE |= SW_1 | SW_2;                  
  P4IES |= SW_1 | SW_2;                 // initial state is rising edge
  
  TA1CTL &= ~TIMER_STOP; 
  TA1CTL &= CLEAR_REGISTER; 
  TA1CTL &= ~TBIE;
  TA1CTL |= TASSEL_1;
  TA1CTL &= ~TIMER_DIVIDE;
  TA1CTL |= TIMER_CONTINUOUS;
  
  TA1CCTL1 &= CLEAR_REGISTER;
}

//------------------------------------------------------------------------------
// Function Name : get_sw_pressed
//
// Description: This is a basic getter for the local sw_pressed field 
// Arguements: void
// Returns:    void                  
//
// Author: Andrew Cragg
// Date: March 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
u_int8 get_sw_pressed()
{
  return sw_pressed_mask;
}