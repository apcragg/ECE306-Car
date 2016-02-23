#include "macros.h"
#include "globals.h"
#include "functions.h"
#include "msp430.h"
#include "shapes.h"

//------------------------------------------------------------------------------
// Function Declarations
    void Switches_Process(u_int8);
    void setup_sw_debounce(void);
    bool software_debounce(unsigned short volatile*, u_int8);
    void sw_pressed(u_int8);
    void sw_released(u_int8);
//------------------------------------------------------------------------------
    
//------------------------------------------------------------------------------
// Module Scope Globals
    static volatile u_int8 sw_pressed_mask = FALSE;
    static volatile u_int8 sw_down_mask = FALSE;
    
    static u_int8 pressed_count = 0;
    static char buff[2];
//------------------------------------------------------------------------------