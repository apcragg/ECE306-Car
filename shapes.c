//============================================================================//
// File Name : shapes.c
//
// Description: This file contains the pulse width modulaition code
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//============================================================================//

#include "shapes.h"

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
      default: break;
    }
  }
}

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
  
  five_msec_sleep(SECOND * 2);
  
  turn_off_motor(R_FORWARD);
  turn_off_motor(L_FORWARD);
  
  is_running = FALSE;
}


