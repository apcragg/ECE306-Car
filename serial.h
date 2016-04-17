#ifndef SERIAL_H
#define SERIAL_H

#include "macros.h"
#include "globals.h"
#include "functions.h"
#include "msp430.h"
#include "timers.h"


//------------------------------------------------------------------------------
// Function Declarations
   void init_serial_uart(void);
   u_int8 get_current_baud(void);
   
   void uca0_set_current_baud(u_int8);
   void uca0_receive_char(char);
   void uca0_transmit_message(char*, int);
   void uca0_transmit_char(void);
   BufferString uca0_read_buffer(u_int8);
   u_int8 uca0_is_message_received();
   
   void uca1_set_current_baud(u_int8);
   void uca1_receive_char(char);
   void uca1_transmit_message(char*, int);
   void uca1_transmit_char(void);
   BufferString uca1_read_buffer(u_int8);
   u_int8 uca1_is_message_received();
   
   
   void transmit_loop(void);
//------------------------------------------------------------------------------
    
//------------------------------------------------------------------------------
// Globals
   
//------------------------------------------------------------------------------

#endif