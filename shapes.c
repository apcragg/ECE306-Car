//============================================================================//
// File Name : shapes.c
//
// Description: This file contains the  shape driving code
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//============================================================================//

#include "shapes.h"

//------------------------------------------------------------------------------
// Function Name : handle_input
//
// Description: This function takes the passed count value and decides which
//              shape to run based on that value.
// Arguements: u_int8           sw_pressed_mask
//             u_int8           sw_pressed_count        
// Returns:    void
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void handle_input(u_int8 sw_pressed_mask, u_int8 sw_pressed_count)
{
  if(is_running)
  {
    is_running = FALSE;
    turn_off_motor(R_FORWARD);
    turn_off_motor(L_FORWARD);
  }
  else
  {
    is_running = TRUE;
    
    switch(sw_pressed_count)
    {
      case 0: break;
      case 1: 
        turn_on_motor(R_FORWARD);
        turn_on_motor(L_FORWARD);
        break;
      case 2:
        go_circle(2, DIR_LEFT, 1.0f, 1.0f); 
        break;
      case 3:
        go_circle(2, DIR_RIGHT, 1.0f, 1.0f);
        break;
      case 4: 
        go_figure_eight(2, 1.0f, 1.0f);
        break;
      default: break;
    }
  }
}

//------------------------------------------------------------------------------
// Function Name : handle_input
//
// Description: This function drives the car in a circle in the direction which
//              the passed value dictates. It adjusts the radius and length of
//              of the circle based on a passed adjustment factor and runs for
//              a dictated amount of circles.
// Arguements: u_int8           num_circles
//             u_int8           direction    
//             float            radius_adj
//             float            length_adj
// Returns:    void
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void go_circle(u_int8 num_circles, u_int8 direction, 
               float radius_adj, float length_adj)
{
  turn_off_motor(R_FORWARD);
  turn_off_motor(L_FORWARD);
  
  length_adj *= 2*PI * radius_adj;
  
  if(direction == DIR_LEFT)
  {
    set_motor_speed(R_FORWARD, MAX_SPEED);
    set_motor_speed(L_FORWARD, (int) (MAX_SPEED / 2.4f));
  }
  else
  {
    set_motor_speed(L_FORWARD, MAX_SPEED);
    set_motor_speed(R_FORWARD, (int) (MAX_SPEED / 2.4f));
  }
  
  turn_on_motor(R_FORWARD);
  turn_on_motor(L_FORWARD);
  
  five_msec_sleep(QUARTER_SECOND * 10 * num_circles);
  
  turn_off_motor(R_FORWARD);
  turn_off_motor(L_FORWARD);
  
  is_running = FALSE;
}

//------------------------------------------------------------------------------
// Function Name : go_figure_eight
//
// Description: This function drives the car in a figure eight by using the
//              go_circles function in opposing directions.
// Arguements: u_int8           num_circles   
//             float            radius_adj
//             float            length_adj
// Returns:    void
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void go_figure_eight(u_int8 num_circles, float radius_adj, float length_adj)
{
  int i;
  for(i = 0; i < num_circles; i++)
  {
    go_circle(1, DIR_LEFT, 1.0f, 1.0f); 
    go_circle(1, DIR_RIGHT, 1.0f, 1.0f); 
  }
}


