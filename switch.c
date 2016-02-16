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
void Switches_Process(void){
//------------------------------------------------------------------------------
  u_int8 temp_down = sw_down_mask;
  u_int8 temp_pressed = sw_pressed_mask;
  
  // Sets the display to the pressed count value
  if((temp_pressed & SW_2) && (display_1 == "Current")) 
    pressed_count = (pressed_count + INCREMENT) % NUM_SHAPES;
  
  buff[0] = DIG_TO_CH(pressed_count);
  buff[1] = NULL_TERM;
   
  if ((temp_down & SW1)){
    display_1 = "NCSU";
    posL1 = DISPLAY_LINE_3;
    display_2 = "WOLFPACK";
    posL2 = DISPLAY_LINE_1;
    display_3 = "ECE306";
    posL3 = DISPLAY_LINE_2;
    display_4 = "Andrew C";
    posL4 = DISPLAY_LINE_1;
  }
  if ((temp_down & SW2)) {
    display_1 = "Current";
    posL1 = DISPLAY_LINE_1;
    display_2 = "shape";
    posL2 = DISPLAY_LINE_2;
    display_3 = "Counter";
    posL3 = DISPLAY_LINE_3;
    display_4 = buff;
    posL4 = DISPLAY_LINE_1;
  }
  
  if(temp_down & SW_1)
    P3OUT |= L_REVERSE;
  else
    P3OUT &= ~L_REVERSE;
  
  if(temp_down & SW_2)
    P3OUT |= R_REVERSE;
  else
    P3OUT &= ~R_REVERSE;
  
                                        // Pressed only lasts one cycle
                                        // Down lasts until released
 sw_pressed_mask ^= temp_pressed;
 
 if(temp_pressed & SW_1) handle_input(temp_pressed, pressed_count);
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
  PJOUT ^= IOT_FACTORY;
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
  PJOUT ^= IOT_WAKEUP;
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

#pragma vector = PORT4_VECTOR
__interrupt void SW_PRESSED_ISR(void)
{
 
  u_int8 current_ifg = P4IV >> 1;           // not exactly safe. If ISR 
                                        // interrupted by another ISR both
                                        // will be cleared if happens before
                                        // the first copy 
  
  P4IE &= ~(current_ifg);               // Port interrupts turned off
  
  if((P4IES & current_ifg)) 
  {
    P4IES &= ~current_ifg;                 // Toggle rising/falling edge
    sw_pressed(current_ifg);
  }
  else
  {
    P4IES |= current_ifg;                // Toggle rising/falling edge
    sw_released(current_ifg);
  }

  unsigned int temp_edge = P4IES;
  TA1CCR1 = (TA1R + ((TA1_CLK_F / ONE_MSEC) *
            (temp_edge & current_ifg ? PRESSED_DEBOUNCE : RELEASED_DEBOUNCE))) 
            % UINT_16_MAX;
  
  TA1CCTL1 |= CCIE;
  TA1CCTL1 &= ~CCIFG;

  P4IFG &= ~current_ifg;                
}

#pragma vector = TIMER1_A1_VECTOR
__interrupt void timer_A1_CCR1_interupt(void)
{
  TA1CCTL1 &= ~CCIFG;                   // clears the interupt flag
  TA1CCTL1 &= ~CCIE;
  P4IE |= SW_1 | SW_2; 
}

#pragma vector = TIMER1_A0_VECTOR
__interrupt void timer_A1_CTL_interupt(void)
{
  TA1CTL &= ~CCIFG;                   // clears the interupt flag
}