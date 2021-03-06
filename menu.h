#ifndef MENU_H
#define MENU_H

#include "macros.h"
#include "globals.h"
#include "msp430.h"
#include "switch.h"
#include "line.h"
#include "adc.h"
#include "serial.h"
#include "functions.h"
#include "string.h"
#include "command.h"

//------------------------------------------------------------------------------
// Function Declarations
    void update_menu(void);
    void menu_handle_input(u_int8);
//------------------------------------------------------------------------------

#endif
