//============================================================================//
// File Name : commands.c
//
// Description: This file contains the IOT wifi module serial command code.
// Author: Andrew Cragg
// Date: April 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//============================================================================//

#include "command.h"

//------------------------------------------------------------------------------
// Module Scope Globals
//------------------------------------------------------------------------------


// Temp Defines
#define COMMAND_AKNOWLEDGE         ("~~")
#define AKNOWLEDGE_MESSAGE         ("Good News Everyone!\n\r")
#define SLOW_BAUD                  ("~S")
#define SLOW_BAUD_MESSAGE          ("Set 9600B\n\r")
#define SLOW_BAUD_COMMAND          ("AT+S.SCFG=console1_speed,9600\r")
#define FAST_BAUD                  ("~F")
#define FAST_BAUD_MESSAGE          ("Set 115200B\n\r")
#define SAVE_COMMAND               ("AT&W\r")
#define RESET_COMMAND              ("AT+CFUN=1\r")
#define RESET_MESSAGE              ("IOT Device Reset")
#define G_MAC_COMMAND              ("AT+S.GCFG=nv_wifi_macaddr\r")

void receive_command(char* command)
{
  if(compare(command, COMMAND_AKNOWLEDGE))
  {
    uca0_transmit_message(AKNOWLEDGE_MESSAGE, NO_OFFSET);
  }
  else if(compare(command, SLOW_BAUD))
  {
    uca1_set_current_baud(BAUD_115200);
    
    uca0_transmit_message(SLOW_BAUD_MESSAGE, NO_OFFSET);  
    uca1_transmit_message(SLOW_BAUD_COMMAND, NO_OFFSET);  
    
    five_msec_delay(SECOND + SECOND);
    
    uca1_transmit_message(SAVE_COMMAND, NO_OFFSET); 
    
    
    five_msec_delay(SECOND);
    uca1_set_current_baud(BAUD_9600);
    
    uca1_transmit_message(RESET_COMMAND, NO_OFFSET);
    PJOUT &= ~IOT_RESET;
    
    five_msec_delay(QUARTER_SECOND);
    
    PJOUT |= IOT_RESET;  
    
    uca0_transmit_message(RESET_MESSAGE, NO_OFFSET);
    
    five_msec_delay(QUARTER_SECOND);
    
    uca1_transmit_message(G_MAC_COMMAND, NO_OFFSET);
  }
  else if(compare(command, FAST_BAUD))
  {
    uca1_set_current_baud(BAUD_115200);
    uca0_transmit_message(FAST_BAUD_MESSAGE, NO_OFFSET);
  }
}
