#ifndef LINES_H
#define LINES_H

#include "macros.h"
#include "globals.h"
#include "msp430.h"

static u_int8 conversion_flag = FALSE; // eh maybe?

//------------------------------------------------------------------------------
// Function Declarations
    void init_adc(void);
    void set_conversion_flag(u_int8);
    int analog_read(int);
//------------------------------------------------------------------------------

#endif
