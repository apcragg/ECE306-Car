#ifndef LINE_H
#define LINE_H

#include "macros.h"
#include "globals.h"
#include "msp430.h"

static int black_cal = MAX_ADC10;
static int white_cal = MIN_ADC10;

//------------------------------------------------------------------------------
// Function Declarations
    void calibrate_sensors(void);
//------------------------------------------------------------------------------

#endif
