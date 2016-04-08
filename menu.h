#ifndef MENU_H
#define MENU_H

#include "macros.h"
#include "globals.h"
#include "msp430.h"
#include "switch.h"
#include "line.h"
#include "adc.h"
#include "serial.h"

//------------------------------------------------------------------------------
// Function Declarations
    void update_menu(void);
    void menu_handle_input(u_int8);
    void update_main_menu();
    void update_resistor_menu();
    void update_shape_menu();
    void update_song_menu();
    void blink_menu_selection(int);
//------------------------------------------------------------------------------

#endif
