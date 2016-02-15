#include "macros.h"
#include "globals.h"
#include "functions.h"
#include "msp430.h"

//------------------------------------------------------------------------------
// Function Declarations
    void Switches_Process(void);
    void setup_sw_debounce(void);
    bool software_debounce(unsigned short volatile*, u_int8);
    void sw_pressed(u_int8);
    void sw_released(u_int8);
//------------------------------------------------------------------------------
    
//------------------------------------------------------------------------------
// Module Scope Globals
    static volatile u_int8 sw_pressed_mask = FALSE;
//------------------------------------------------------------------------------