//============================================================================//
// File Name : motor.c
//
// Description: This file contains the motor control functions. This assumes
//              R_FORWARD is on a pin with TB1.1
//              L_FORWARD is on a pin with TB2.1
//              R_REVERSE is on a pin with TB1.2
//              L_FORWARD is on a pin with TB2.2
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//============================================================================//

#include "msp430.h"
#include "macros.h"
#include "motor.h"
#include "timers.h"


//------------------------------------------------------------------------------
// Function Name : right_forward DEPRECATED DON'T USE
//
// Description: This function turns on the right motor going forward.
//              First it ensures the reverse drive is turned off
// Arguements: void
// Returns:    void
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void inline right_forward()
{
  if(!(P3OUT & R_FORWARD))
  {
     P3OUT &= ~R_REVERSE;
     P3OUT |= R_FORWARD;
  }
}

//------------------------------------------------------------------------------
// Function Name : left_forward DEPRECATED DON'T USE
//
// Description: This function turns on the left motor going forward.
//              First it ensures the reverse drive is turned off
// Arguements: void
// Returns:    void
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void inline left_forward()
{
   if(!(P3OUT & L_FORWARD))
   {
     P3OUT &= ~L_REVERSE;
     P3OUT |= L_FORWARD;
   }
}

//------------------------------------------------------------------------------
// Function Name : turn_on_motor
//
// Description: This function sets turns the passed motor off
// Arguements: u_int8                   motor
// Returns:    void
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void turn_on_motor(u_int8 motor)
{
  switch(motor)
  {                  
    case R_FORWARD: turn_off_motor(R_REVERSE); enable_pwm(&TB1CCTL1); break;
    case L_FORWARD: turn_off_motor(L_REVERSE); enable_pwm(&TB2CCTL1); break;
    case R_REVERSE: turn_off_motor(R_FORWARD); enable_pwm(&TB1CCTL2); break;
    case L_REVERSE: turn_off_motor(L_FORWARD); enable_pwm(&TB2CCTL2); break;
  }
}

//------------------------------------------------------------------------------
// Function Name : turn_off_motor
//
// Description: This function sets turns the passed motor off
// Arguements: u_int8                   motor
// Returns:    void
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void turn_off_motor(u_int8 motor)
{
  switch(motor)
  {                  
    case R_FORWARD: disable_pwm(&TB1CCTL1); P3OUT &= ~motor; break;
    case L_FORWARD: disable_pwm(&TB2CCTL1); P3OUT &= ~motor; break;
    case R_REVERSE: disable_pwm(&TB1CCTL2); P3OUT &= ~motor; break;
    case L_REVERSE: disable_pwm(&TB2CCTL2); P3OUT &= ~motor; break;
  }
}

//------------------------------------------------------------------------------
// Function Name : set_motor_speed
//
// Description: This function sets the motor speed via changing the PWM value
//              Due to a slower motor I have it also corrects this.
// Arguements: u_int8                   motor
//             int                      motor_speed
// Returns:    void
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void set_motor_speed(u_int8 motor, int motor_speed)
{
  switch(motor)
  {                  // compensates for slow motor I have
    case R_FORWARD: 
      set_pwm_value(&TB1CCR1, (int) (PWM_RES - (motor_speed * MOTOR_ADJ_FAC))); break;
    case L_FORWARD: 
      set_pwm_value(&TB2CCR1, PWM_RES - motor_speed); break;
     case R_REVERSE: 
      set_pwm_value(&TB1CCR2, (int) (PWM_RES - (motor_speed * MOTOR_ADJ_FAC))); break;
    case L_REVERSE: 
      set_pwm_value(&TB2CCR2, PWM_RES - motor_speed); break;
  }
}

//------------------------------------------------------------------------------
// Function Name : active_brake
//
// Description: This function activly brakes the car by turn the reverse motors
//              on hard for a breif moment.
// Arguements: void
// Returns:    void
//
// Author: Andrew Cragg
// Date: March 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void active_brake()
{
  turn_off_motor(R_FORWARD);
  turn_off_motor(L_FORWARD);
  
  turn_on_motor(R_REVERSE);      // Active braking
  turn_on_motor(L_REVERSE);
  
  five_msec_delay(ACTIVE_BREAK); // Active braking time constant
  
  turn_off_motor(R_REVERSE);
  turn_off_motor(L_REVERSE);
}

//------------------------------------------------------------------------------
// Function Name : active_brake_reverse
//
// Description: This function activly brakes the car by turn the forward motors
//              on hard for a breif moment.
// Arguements: void
// Returns:    void
//
// Author: Andrew Cragg
// Date: March 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void active_brake_reverse()
{
  turn_off_motor(R_REVERSE);
  turn_off_motor(L_REVERSE);
  
  turn_on_motor(R_FORWARD);      // Active braking
  turn_on_motor(L_FORWARD);
  
  five_msec_delay(ACTIVE_BREAK); // Active braking time constant
  
  turn_off_motor(R_FORWARD);
  turn_off_motor(L_FORWARD);
}