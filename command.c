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
#define FAST_BAUD                  ("~F")
#define FAST_BAUD_MESSAGE          ("Set 115kB\n\r")

void receive_command(char* command)
{
  if(compare(command, COMMAND_AKNOWLEDGE))
  {
    uca0_transmit_message(AKNOWLEDGE_MESSAGE);
  }
  else if(compare(command, SLOW_BAUD))
  {
    uca1_set_current_baud(BAUD_9600);
    uca0_transmit_message(SLOW_BAUD_MESSAGE);
  }
  else if(compare(command, FAST_BAUD))
  {
    uca1_set_current_baud(BAUD_115200);
    uca0_transmit_message(FAST_BAUD_MESSAGE);
  }
}
