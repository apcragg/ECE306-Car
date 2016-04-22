#ifndef LINE_H
#define LINE_H

#include "macros.h"
#include "globals.h"
#include "msp430.h"
#include "adc.h"
#include "motor.h"
#include "timers.h"
#include "functions.h"

static int r_black_cal = 0x22b;
static int r_white_cal = 0x40;
static int l_black_cal = 0x22b;
static int l_white_cal = 0x40;

//------------------------------------------------------------------------------
// Function Declarations
    void calibrate_sensors(u_int8);
    u_int8 determine_line(u_int8);
    void run_follow();
    void run_basic();
//------------------------------------------------------------------------------

#endif
