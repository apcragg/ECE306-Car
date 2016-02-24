#ifndef TIMERS_H
#define TIMERS_H

#include "macros.h"
#include "globals.h"
#include "functions.h"
#include "msp430.h"

//------------------------------------------------------------------------------
// Function Declarations
    void five_msec_delay(unsigned int delay);
    void init_timers(void);
    void init_timer_A0(void);
    void increment_timer_count();
    unsigned int get_timer_count();  
//------------------------------------------------------------------------------
    
//------------------------------------------------------------------------------
// Module Scope Globals
    static unsigned volatile int timer_count = START_VAL;
//------------------------------------------------------------------------------

#endif