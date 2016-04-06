#ifndef SERIAL_H
#define SERIAL_H

#include "macros.h"
#include "globals.h"
#include "functions.h"
#include "msp430.h"

//------------------------------------------------------------------------------
// Function Declarations
   void init_serial_uart(void);
   u_int8 get_current_baud();
   void set_current_baud(u_int8);
   void receive_char(char);
   void transmit_message(char*);
   void transmit_char();
   char* read_buffer();
   u_int8 is_message_received();
//------------------------------------------------------------------------------
    
//------------------------------------------------------------------------------
// Globals
    
//------------------------------------------------------------------------------

#endif