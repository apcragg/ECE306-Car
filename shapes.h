#ifndef SHAPES_H
#define SHAPES_H

#include "macros.h"
#include "motor.h"
#include "globals.h"
#include "functions.h"
#include "timers.h"

void five_msec_sleep(unsigned int);

//------------------------------------------------------------------------------
// Function Declarations
    void go_circle(u_int8, u_int8, float, float);
    void go_triangle(u_int8, u_int8, float, float);
    void go_figure_eight(u_int8, float, float);
    void go_back_and_forth(void);
    void handle_input(u_int8, u_int8);
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Module Scope Globals
    static bool is_running = FALSE;
//------------------------------------------------------------------------------

#endif