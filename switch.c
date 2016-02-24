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
void Switches_Process(u_int8 is_interrupt){
//------------------------------------------------------------------------------
  u_int8 temp_down = sw_down_mask;
  u_int8 temp_pressed = sw_pressed_mask;
  
  // Sets the display to the pressed count value
  if((temp_pressed & SW_2)) 
    pressed_count = (pressed_count + INCREMENT) % NUM_SHAPES;
  
  buff[0] = DIG_TO_CH(pressed_count);
  buff[1] = NULL_TERM;
   
  if ((temp_down & SW1)){
    display_1 = "Running";
    posL1 = DISPLAY_LINE_3;
    display_2 = "Program";
    posL2 = DISPLAY_LINE_1;
    display_3 = "...";
    posL3 = DISPLAY_LINE_2;
    display_4 = " ";
    posL4 = DISPLAY_LINE_1;
  }
  if ((temp_down & SW2)) {
    display_1 = "Current";
    posL1 = DISPLAY_LINE_1;
    display_2 = "Action";
    posL2 = DISPLAY_LINE_1;
    display_3 = " ";
    posL3 = DISPLAY_LINE_1;
    display_4 = buff;
    posL4 = DISPLAY_LINE_1;
  } 
                                        // Pressed only lasts one cycle
                                        // Down lasts until released
 sw_pressed_mask ^= temp_pressed;
 
 if((temp_pressed & SW_1) && !is_interrupt) 
   handle_input(temp_pressed, pressed_count);
//------------------------------------------------------------------------------
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
  
  //Switches_Process(TRUE);
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
  //Switches_Process(TRUE);
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