#ifndef MOTOR_H
#define MOTOR_H

#include "pwm.h"

//------------------------------------------------------------------------------
// Function Declarations
    void right_forward(void);
    void left_forward(void);
    void turn_on_motor(u_int8);
    void turn_off_motor(u_int8);
    void set_motor_speed(u_int8, int);
    void active_brake();
    void active_brake_reverse();
//------------------------------------------------------------------------------

#endif