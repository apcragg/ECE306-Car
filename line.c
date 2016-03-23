//============================================================================//
// File Name : line.c
//
// Description: This file contains the black line following code.
//
// Author: Andrew Cragg
// Date: March 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//============================================================================//

#include "line.h"

//------------------------------------------------------------------------------
// Function Name : calibrate_sensors
//
// Description: This function calibrates the sensors for the white and black
//              surface using prompts to the user.
// Arguements: unsigned int     delay
// Returns:    void
//
// Author: Andrew Cragg
// Date: March 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void calibrate_sensors(u_int8 type)
{
  if(type == BLACK_VAL)
  {
    black_cal = (analog_read(ADC0) + analog_read(ADC1)) / AVG_2;
  }
  else if(type == WHITE_VAL)
  {
    white_cal = (analog_read(ADC0) + analog_read(ADC1)) / AVG_2;
  }
}

//------------------------------------------------------------------------------
// Function Name : calibrate_sensors
//
// Description: This function calibrates the sensors for the white and black
//              surface using prompts to the user.
// Arguements: unsigned int     delay
// Returns:    void
//
// Author: Andrew Cragg
// Date: March 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
u_int8 determine_line(u_int8 side)
{
  u_int8 detection = WHITE_VAL;
  int adc_val = MIN_ADC10;
  
  if(side == RIGHT_DETECT)
  {
    adc_val = analog_read(ADC0);
    
    if(ABS(black_cal - adc_val) < ABS(white_cal - adc_val))
      detection = BLACK_VAL;
  }
  else if(side == LEFT_DETECT)
  {
    adc_val = analog_read(ADC1);
    
    if(ABS(black_cal - adc_val) < ABS(white_cal - adc_val))
      detection = BLACK_VAL;
  }
  
  return detection;
}

//------------------------------------------------------------------------------
// Function Name : run_basic
//
// Description: This function runs the basic line following program
// Arguements: void
// Returns:    void
//
// Author: Andrew Cragg
// Date: March 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void run_basic()
{
  int line_count = START_VAL;
  long int start_time;
  long int elapsed_time;
  long int msec_time;
  
  char timer_buffer[LCD_LENGTH];
  
  display_1 = "Running";
  display_2 = "Forward";
  display_3 = " ";
  display_4 = " ";
   
   display_2 = " ";
   Display_Process();
  
  set_motor_speed(L_FORWARD, MAX_SPEED);
  set_motor_speed(R_FORWARD, MAX_SPEED);
  
  set_motor_speed(L_REVERSE, MAX_SPEED);
  set_motor_speed(R_REVERSE, MAX_SPEED);

  turn_on_motor(R_FORWARD);
  five_msec_delay(TURN_ON_COMP);
  turn_on_motor(L_FORWARD);
  
  while(line_count < TRIGGER_COUNT) // Kill time until hit black line
  {
    if(determine_line(RIGHT_DETECT) == BLACK_VAL)
      line_count++;
    if(determine_line(LEFT_DETECT) == BLACK_VAL)
      line_count++;
  }
  
  active_brake();
  
  five_msec_delay(SECOND + HALF_SECOND); // 1.5 sec Pause
  
  display_2 = "Reverse";
  Display_Process();
  
  start_time = system_time;
  
  turn_on_motor(L_REVERSE);
  turn_on_motor(R_REVERSE);
  
  five_msec_delay(HALF_SECOND); // Allow car to travel back over line
  
  display_2 = "Forward";
  display_3 = "Timer:";
  Display_Process();
  
  line_count = START_VAL;
  
   while(line_count < TRIGGER_COUNT) // Kill time until hit black line
  {
    if(determine_line(RIGHT_DETECT) == BLACK_VAL)
      line_count++;
    if(determine_line(LEFT_DETECT) == BLACK_VAL)
      line_count++;
  }
  
  active_brake_reverse();
  
  elapsed_time = system_time - start_time;
    
  msec_time = elapsed_time * BY_FIVE;
  timer_buffer[0] = (((msec_time % (THOUSANDS * TENS)) -
                     (msec_time % THOUSANDS)) / THOUSANDS) + '0';
  timer_buffer[1] = (((msec_time % THOUSANDS) - 
                      (msec_time % HUNDREDS)) / HUNDREDS) + '0';
  timer_buffer[2] = (((msec_time % HUNDREDS) - 
                      (msec_time % TENS)) / TENS) + '0';
  timer_buffer[3] = (((msec_time % TENS) % TENS)) + '0';
  timer_buffer[4] = NULL_TERM;
  
  display_2 = "Idling";
  display_4 = timer_buffer;
  Display_Process();
  
  five_msec_delay(FIVE_SECONDS); // 5 sec Pause
  
  display_2 = "Forward";
  Display_Process();
  
  turn_on_motor(R_FORWARD);
  five_msec_delay(TURN_ON_COMP);
  turn_on_motor(L_FORWARD);
  
  five_msec_delay((elapsed_time / AVG_2) + QUARTER_SECOND);
  
  active_brake();
  
  display_2 = "CounterCLK";
  Display_Process();
  
  turn_on_motor(R_FORWARD);
  turn_on_motor(L_REVERSE);
  
  
  five_msec_delay((FIVE_SECONDS / AVG_2) + HALF_SECOND + QUARTER_SECOND);
  
  active_brake_reverse();
  
  display_2 = "Clockwise";
  Display_Process();
  
  turn_on_motor(L_FORWARD);
  turn_on_motor(R_REVERSE);
  
  five_msec_delay((FIVE_SECONDS - SECOND - QUARTER_SECOND));
  
  active_brake();
}