#ifndef LINE_H
#define LINE_H

#include "macros.h"
#include "globals.h"
#include "msp430.h"
#include "adc.h"
#include "motor.h"
#include "timers.h"
#include "functions.h"

static int black_cal = MAX_ADC10;
static int white_cal = MIN_ADC10;

//------------------------------------------------------------------------------
// Function Declarations
    void calibrate_sensors(u_int8);
    u_int8 determine_line(u_int8);
    void run_basic();
//------------------------------------------------------------------------------

#endif
