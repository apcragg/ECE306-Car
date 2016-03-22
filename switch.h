#ifndef SWITCH_H
#define SWITCH_H

#include "macros.h"
#include "globals.h"
#include "functions.h"
#include "msp430.h"
#include "shapes.h"
#include "menu.h"

//------------------------------------------------------------------------------
// Function Declarations
    void update_switches(void);
    void setup_sw_debounce(void);
    bool software_debounce(unsigned short volatile*, u_int8);
    void sw_pressed(u_int8);
    void sw_released(u_int8);
    u_int8 get_sw_pressed(void);
//------------------------------------------------------------------------------

    
#endif