//============================================================================//
// File Name : motor.c
//
// Description: This file contains the motor control functions
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//============================================================================//

#include "msp430.h"
#include "macros.h"
#include "motor.h"

    
void inline right_forward()
{
  if(!(P3OUT & R_FORWARD))
  {
     P3OUT &= ~R_REVERSE;
     P3OUT |= R_FORWARD;
  }
}

void inline left_forward()
{
   if(!(P3OUT & L_FORWARD))
   {
     P3OUT &= ~L_REVERSE;
     P3OUT |= L_FORWARD;
   }
}

void inline turn_motor_off(u_int8 motor)
{
   P3OUT &= ~(motor);
}

void set_motor_speed(u_int8 motor, int motor_speed)
{
  switch(motor)
  {                  // compensates for slow motor I have
    case R_FORWARD: set_pwm_value(&TB1CCR1, (int) (PWM_RES - (motor_speed * MOTOR_ADJ_FAC))); break;
    case L_FORWARD: set_pwm_value(&TB2CCR1, PWM_RES - motor_speed); break;
  }
}
