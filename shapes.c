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
    turn_off_motor(R_REVERSE);
    turn_off_motor(L_REVERSE);
  }
  else
  {
    is_running = TRUE;

    switch(sw_pressed_count)
    {
      case 0: break;
      case 1:
        go_back_and_forth();
        break;
      case 2:
        go_circle(2, DIR_LEFT, 1.0f, 1.1f);
        break;
      case 3:
        go_circle(2, DIR_RIGHT, 1.0f, 1.1);
        break;
      case 4:
        go_figure_eight(2, 1.0f, 1.0f);
        break;
      case 5:
        go_triangle(2, DIR_LEFT, 1.0f, 1.0f);
        break;
      case 6:
        break;
      default: break;
    }
  }
}

//------------------------------------------------------------------------------
// Function Name : go_circle
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
// Magic numbers used in real world calibration
// Wouldn't make sense to hide in Macors.h
  turn_off_motor(R_FORWARD);
  turn_off_motor(L_FORWARD);
  
  length_adj *= (direction == R_FORWARD ? R_LEN_COMP : 1.0f) 
             * BATT_COMP * radius_adj;

  if(direction == DIR_LEFT)
  {
    set_motor_speed(R_FORWARD, MAX_SPEED);
    set_motor_speed(L_FORWARD, (int) (MAX_SPEED * 0.4 * radius_adj));
  }
  else
  {
    set_motor_speed(L_FORWARD, MAX_SPEED);
    set_motor_speed(R_FORWARD, (int) (MAX_SPEED * 0.377f * radius_adj));
  }

  turn_on_motor(R_FORWARD);
  turn_on_motor(L_FORWARD);

  unsigned int delay = (unsigned int)(((float) QUARTER_SECOND * 5.07f * (float) num_circles) * length_adj);
  five_msec_delay(delay);

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
    go_circle(1, DIR_LEFT, 0.87f, 1.075f); // magic calibration numbers
    go_circle(1, DIR_RIGHT, 0.87f,
              i == num_circles - OFF_BY_ONE_OFFSET ? 0.9f : .96f);
  }
}

//------------------------------------------------------------------------------
// Function Name : go_triangle
//
// Description: This function drives the car in a triangle in the direction
//              the passed value dictates. It adjusts the radius and length of
//              of the turns based on a passed adjustment factor and runs for
//              a dictated amount of triangles.
// Arguements: u_int8           num_triangles
//             u_int8           direction
//             float            radius_adj
//             float            length_adj
// Returns:    void
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void go_triangle(u_int8 num_triangles, u_int8 direction,
               float radius_adj, float length_adj)
{
  turn_off_motor(R_FORWARD);
  turn_off_motor(L_FORWARD);

  length_adj *= (direction == R_FORWARD ? R_LEN_COMP : UN_COMP) * BATT_COMP;

  int i;

  for(i = 0; i < num_triangles * NUM_TRI_PTS; i++)
  {
    if(direction == DIR_LEFT)
    {
      set_motor_speed(R_FORWARD, MAX_SPEED);
      set_motor_speed(L_FORWARD, MOTOR_SPD_OFF);
    }
    else
    {
      set_motor_speed(L_FORWARD, MAX_SPEED);
      set_motor_speed(R_FORWARD, MOTOR_SPD_OFF);
    }

    turn_on_motor(R_FORWARD);
    turn_on_motor(L_FORWARD);

    five_msec_delay((unsigned int) (length_adj * (QUARTER_SECOND) * 1.15f));

    turn_off_motor(R_FORWARD);
    turn_off_motor(L_FORWARD);

    set_motor_speed(R_FORWARD, MAX_SPEED);
    set_motor_speed(L_FORWARD, MAX_SPEED);

    turn_on_motor(R_FORWARD);
    turn_on_motor(L_FORWARD);

    five_msec_delay((QUARTER_SECOND * 2) / 2);

    turn_off_motor(R_FORWARD);
    turn_off_motor(L_FORWARD);
  }

  is_running = FALSE;
}


//------------------------------------------------------------------------------
// Function Name : go_back_and_forth
//
// Description: This function drives the car in the way presribed by project 4
// Arguements: void
// Returns:    void
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void go_back_and_forth(void)
{
    five_msec_delay(SECOND);
  
    set_motor_speed(R_FORWARD, MAX_SPEED);
    set_motor_speed(L_FORWARD, MAX_SPEED);
    set_motor_speed(R_REVERSE, MAX_SPEED);
    set_motor_speed(L_REVERSE, MAX_SPEED);
  
    // Forward 1 sec
    display_3 = "Forward";
    Display_Process();
    
    turn_on_motor(R_FORWARD);
    turn_on_motor(L_FORWARD);
    
    five_msec_delay(SECOND);
    
    turn_off_motor(R_FORWARD);
    turn_off_motor(L_FORWARD);
    
    five_msec_delay(SECOND);
    
    // Reverse 2 sec
    display_3 = "Reverse";
    Display_Process();
    
    turn_on_motor(R_REVERSE);
    turn_on_motor(L_REVERSE);
    
    five_msec_delay(SECOND * 2u);
    
    turn_off_motor(R_REVERSE);
    turn_off_motor(L_REVERSE);
    
    five_msec_delay(SECOND);
    
    // Forward 1 sec
    display_3 = "Forward";
    Display_Process();
    
    turn_on_motor(R_FORWARD);
    turn_on_motor(L_FORWARD);
    
    five_msec_delay(SECOND);
    
    turn_off_motor(R_FORWARD);
    turn_off_motor(L_FORWARD);
    
    five_msec_delay(SECOND);
    
    // Clockwise 1 sec
    display_3 = "Clockwise";
    Display_Process();
    
    turn_on_motor(R_REVERSE);
    turn_on_motor(L_FORWARD);
    
    five_msec_delay(SECOND);
    
    turn_off_motor(R_REVERSE);
    turn_off_motor(L_FORWARD);
    
    five_msec_delay(SECOND);
    
    // Counterclockwise 1 sec
    display_3 = "Counterclk";
    Display_Process();
    
    turn_on_motor(L_REVERSE);
    turn_on_motor(R_FORWARD);
    
    five_msec_delay(SECOND);
    
    turn_off_motor(L_REVERSE);
    turn_off_motor(R_FORWARD);
    
    five_msec_delay(SECOND);
}


