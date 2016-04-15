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
#define CONNECT_NCSU               ("~WIFI.C.NCSU")
#define CONNECT_NCSU_MESSAGE       ("Connecting to NCSU WiFi at SSID ")
#define SET_SSID_NCSU_COMMAND      ("AT+S.SSIDTXT=ncsu\r")
#define GET_SSID_NCSU_COMMAND      ("AT+S.SSIDTXT\r")
#define SET_HOST_NAME_COMMAND      ("AT+S.SCFG=ip_hostname,ECE306_01_AN\r")
#define GET_HOST_NAME_COMMAND      ("AT+S.GCFG=ip_hostname\r")
#define SET_PRIVACY_MODE_COMMAND   ("AT+S.SCFG=wifi_priv_mode,0\r")
#define GET_PRIVACY_MODE_COMMAND   ("AT+S.GCFG=wifi_priv_mode\r")
#define SET_NETWORK_MODE_COMMAND   ("AT+S.SCFG=wifi_mode,1\r")
#define GET_NETWORK_MODE_COMMAND   ("AT+S.GCFG=wifi_mode\r")
#define GET_WIFI_STATUS            ("~WIFI.S")
#define GET_WIFI_STATUS_COMMAND    ("AT+S.STS\r")

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
  else if(compare(command, CONNECT_NCSU))
  {
    uca0_transmit_message(CONNECT_NCSU_MESSAGE, NO_OFFSET);    
    uca1_transmit_message(SET_SSID_NCSU_COMMAND, NO_OFFSET);
    uca1_transmit_message(GET_SSID_NCSU_COMMAND, NO_OFFSET);
    
    five_msec_delay(QUARTER_SECOND);
    
    uca1_transmit_message(SET_HOST_NAME_COMMAND, NO_OFFSET);
    uca1_transmit_message(GET_HOST_NAME_COMMAND, NO_OFFSET);
    
    five_msec_delay(QUARTER_SECOND);
    
    uca1_transmit_message(SET_PRIVACY_MODE_COMMAND, NO_OFFSET);
    uca1_transmit_message(GET_PRIVACY_MODE_COMMAND, NO_OFFSET);
    
    five_msec_delay(QUARTER_SECOND);
    
    uca1_transmit_message(SET_NETWORK_MODE_COMMAND, NO_OFFSET);
    uca1_transmit_message(GET_NETWORK_MODE_COMMAND, NO_OFFSET);
    
    uca1_transmit_message(SAVE_COMMAND, NO_OFFSET);
    uca1_transmit_message(GET_NETWORK_MODE_COMMAND, NO_OFFSET);
    
    uca1_transmit_message(SAVE_COMMAND, NO_OFFSET);
    
    five_msec_delay(QUARTER_SECOND);
    
    uca1_transmit_message(RESET_COMMAND, NO_OFFSET);
    PJOUT &= ~IOT_RESET;
    
    five_msec_delay(QUARTER_SECOND);    
    PJOUT |= IOT_RESET;  
    
    uca0_transmit_message(RESET_MESSAGE, NO_OFFSET);   
  }
  else if(compare(command, GET_WIFI_STATUS))
  {
    uca1_transmit_message(GET_WIFI_STATUS_COMMAND, NO_OFFSET);
  }
}
