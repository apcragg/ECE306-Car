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

static char buffer[DISPLAY_LENGTH] = "0";

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
    l_black_cal = analog_read(ADC0);
    r_black_cal = analog_read(ADC1);
  }
  else if(type == WHITE_VAL)
  {
    l_white_cal = analog_read(ADC0);
    r_white_cal = analog_read(ADC1);
  }
}

//------------------------------------------------------------------------------
// Function Name : determine_line
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
    
    if(ABS(l_black_cal - adc_val) < ABS(l_white_cal - adc_val))
      detection = BLACK_VAL;
  }
  else if(side == LEFT_DETECT)
  {
    adc_val = analog_read(ADC1);
    
    if(ABS(l_black_cal - adc_val) < ABS(l_white_cal - adc_val))
      detection = BLACK_VAL;
  }
  
  return detection;
}

//------------------------------------------------------------------------------
// Function Name : run_follow
//
// Description: This function runs the full line following program. It uses 
//              simplified PID control.
// Arguements: void
// Returns:    void
//
// Author: Andrew Cragg
// Date: April 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void run_follow()
{
  static int current_side_error = ON_LINE;
  static int previous_error = NO_ERROR;
  static int integral_error = NO_ERROR;
  
  int left_val, right_val, left_err, right_err, error;
  int l_base_speed = (int) (MAX_SPEED * 0.160f);
  int r_base_speed = (int) (MAX_SPEED * 0.160f);
  int motor_speed = START_ZERO;
  int l_speed;
  int r_speed;
  
  int kp = 3;
  int kd = 25;
  int ki = 1;

  
  left_val = analog_read(ADC0);
  right_val = analog_read(ADC1);
  
  left_err = l_black_cal - left_val;
  left_err = left_err > ERROR_BASELINE ? left_err - ERROR_BASELINE : NO_ERROR;
  
  right_err = r_black_cal - right_val;
  right_err = right_err > ERROR_BASELINE ? right_err - ERROR_BASELINE : NO_ERROR;
  
  if((left_err == NO_ERROR) && (right_err > NO_ERROR))
  {
    current_side_error = RIGHT_SIDE;
  }
  if((right_err == NO_ERROR) && (left_err > NO_ERROR))
  {
    current_side_error = LEFT_SIDE;
  }
  if((right_err == NO_ERROR) && (left_err == NO_ERROR))
  {
    current_side_error = NO_ERROR;
  }
  
  if(current_side_error == RIGHT_SIDE)
  {
    error = right_err;
  }
  if(current_side_error == LEFT_SIDE)
  {
    error = -left_err;
  }

  if(current_side_error == NO_ERROR)
  {
    l_speed = l_base_speed;
    r_speed = r_base_speed;
  }
  else
  {
    motor_speed = (kp * error) +
                  (kd * (error - previous_error)) +
                  (ki * integral_error / 2);
    
    if(current_side_error == LEFT_SIDE)
    {
      l_speed = l_base_speed - 2*motor_speed;
      r_speed = r_base_speed + 2*motor_speed;
    }
    else
    {
      l_speed = l_base_speed - motor_speed;
      r_speed = r_base_speed + motor_speed;
    }
  }
       
  previous_error = error;
  integral_error += error;
  
  if(integral_error > 600) integral_error = 600;
  if(integral_error < -600) integral_error = -600;
  
  if(l_speed > MAX_LINE_SPEED) l_speed = (int) (MAX_LINE_SPEED * 1.10f);
  if(l_speed < MIN_SPEED) l_speed = MIN_SPEED;
  
  if(r_speed > MAX_LINE_SPEED) r_speed = MAX_LINE_SPEED;
  if(r_speed < MIN_SPEED) r_speed = MIN_SPEED;
  
  set_motor_speed(L_FORWARD, l_speed);
  set_motor_speed(R_FORWARD, r_speed);
  
  turn_on_motor(R_FORWARD);
  turn_on_motor(L_FORWARD);
  
  if(current_side_error == LEFT_SIDE)
    five_msec_delay(16);
  else
    five_msec_delay(14);
  
  turn_off_motor(R_FORWARD);
  turn_off_motor(L_FORWARD);
  
  five_msec_delay(11);
  
  //turn_off_motor(R_FORWARD);
  //turn_off_motor(L_FORWARD);
  
  //five_msec_delay(50);
  
  display_4 = buffer;       
  
  buffer[ARR_POS_0] = DIG_TO_CH(current_side_error);
  buffer[1] = HEX_TO_CH((left_err >> BYTE_SIZE  ) & NIBBLE);
  buffer[2] = HEX_TO_CH((left_err >> NIBBLE_SIZE) & NIBBLE);
  buffer[3] = HEX_TO_CH((left_err               ) & NIBBLE);
  buffer[4] = '-';
  buffer[5] = HEX_TO_CH((right_err >> BYTE_SIZE  ) & NIBBLE);
  buffer[6] = HEX_TO_CH((right_err >> NIBBLE_SIZE) & NIBBLE);
  buffer[7] = HEX_TO_CH((right_err               ) & NIBBLE);
  buffer[8] = NULL_TERM;
  buffer[9] = NULL_TERM;
  buffer[10] = NULL_TERM;
  
  /*buffer[ARR_POS_0] = '0';
  buffer[ARR_POS_1] = 'x';
  buffer[ARR_POS_2] = HEX_TO_CH((right_err >> BYTE_SIZE  ) & NIBBLE);
  buffer[ARR_POS_3] = HEX_TO_CH((right_err >> NIBBLE_SIZE) & NIBBLE);
  buffer[ARR_POS_4] = HEX_TO_CH((right_err)                & NIBBLE);
  buffer[ARR_POS_5] = NULL_TERM;*/
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
  
}

/*// Detect What side of the line currently on
  if(!current_side_error && (right_err > left_err))
  {
    current_side_error = RIGHT_SIDE;
    
  }
  else if(!current_side_error && (left_err > right_err)) 
  {
    current_side_error = LEFT_SIDE; 
  }
  else if((left_err == 0) && (right_err == 0))
  {
    current_side_error = NO_ERROR; 
  }
  
  if(current_side_error == RIGHT_SIDE)
  {
    set_motor_speed(R_FORWARD, (int) (right_power * 1.0f));
    set_motor_speed(L_REVERSE, (int) (left_power * .85f));
    
    turn_on_motor(R_FORWARD);
    turn_on_motor(L_REVERSE);
    
    five_msec_delay(35);
    
    turn_off_motor(R_FORWARD);
    turn_off_motor(L_REVERSE);
  }
  else if(current_side_error == LEFT_SIDE)
  {
    set_motor_speed(R_REVERSE, (int) (right_power * 1.0f));
    set_motor_speed(L_FORWARD, (int) (left_power * .85f));
    
    turn_on_motor(R_REVERSE);
    turn_on_motor(L_FORWARD);
    
    five_msec_delay(35);
    
    turn_off_motor(R_REVERSE);
    turn_off_motor(L_FORWARD);
  }
  else
  {
    set_motor_speed(R_FORWARD, right_power);
    set_motor_speed(L_FORWARD, left_power);
    
    turn_on_motor(R_FORWARD);
    turn_on_motor(L_FORWARD);
    
    five_msec_delay(35);
  }
  
  five_msec_delay(35);*/