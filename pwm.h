#ifndef PWM_H
#define PWM_H

#include "macros.h"

//------------------------------------------------------------------------------
// Function Declarations
    void init_pwm(unsigned short volatile*);
    void set_pwm_resolution(unsigned short volatile*, unsigned int);
    void set_pwm_value(unsigned short volatile*, unsigned int);
    void set_pwm_output(unsigned short volatile*);
    void start_pwm(unsigned short volatile*);
//------------------------------------------------------------------------------

#endif