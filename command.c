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

void receive_command(char* command)
{
  BufferString temp_command;
  temp_command.head = command;
  temp_command.offset = START_ZERO;
  
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
     uca1_set_current_baud(BAUD_9600);
    
    uca0_transmit_message(FAST_BAUD_MESSAGE, NO_OFFSET);  
    uca1_transmit_message(FAST_BAUD_COMMAND, NO_OFFSET);  
    
    five_msec_delay(SECOND + SECOND);
    
    uca1_transmit_message(SAVE_COMMAND, NO_OFFSET); 
    
    
    five_msec_delay(SECOND);
    uca1_set_current_baud(BAUD_115200);
    
    uca1_transmit_message(RESET_COMMAND, NO_OFFSET);
    PJOUT &= ~IOT_RESET;
    
    five_msec_delay(QUARTER_SECOND);
    
    PJOUT |= IOT_RESET;  
    
    uca0_transmit_message(RESET_MESSAGE, NO_OFFSET);
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
  else if(compare(command, GET_WIFI_IP))
  {
    uca1_transmit_message(GET_WIFI_IP_COMMAND, NO_OFFSET);
  }
  // Forward Command
  else if(find(CAR_FORWARD, temp_command))
  {
    display_1 = CLEAR_LINE;
    display_2 = command;
    display_3 = CLEAR_LINE;
    display_4 = CLEAR_LINE;
    
    set_motor_speed(R_FORWARD, (int) (MAX_SPEED * 0.87f));
    set_motor_speed(L_FORWARD, MAX_SPEED);
    
    lcd_BIG_mid();
    five_msec_delay(QUARTER_SECOND);
    Display_Process();
    
    uca0_transmit_message("SUCCESS", NO_OFFSET);    
     
    turn_on_motor(R_FORWARD);
    turn_on_motor(L_FORWARD);
    
    if(CH_TO_DIG(command[COMMAND_TIME_POS]) <= 9)
      five_msec_delay(SECOND * CH_TO_DIG(command[COMMAND_TIME_POS]) / COMMAND_TURN_RATIO);
    
    turn_off_motor(R_FORWARD);
    turn_off_motor(L_FORWARD);
    
     lcd_4line();
     
     if(command[COMMAND_LENGTH] == COMMAND_CHAR_SYMBOL)
       receive_command(command + COMMAND_LENGTH);
  }
  // Backward Command
   else if(find(CAR_BACKWARD, temp_command))
  {
    display_1 = CLEAR_LINE;
    display_2 = command;
    display_3 = CLEAR_LINE;
    display_4 = CLEAR_LINE;
    
    lcd_BIG_mid();
    five_msec_delay(QUARTER_SECOND);
    Display_Process();
    
     uca0_transmit_message("SUCCESS", NO_OFFSET);    
     
    turn_on_motor(R_REVERSE);
    turn_on_motor(L_REVERSE);
    
    five_msec_delay(SECOND * CH_TO_DIG(command[COMMAND_TIME_POS]));
    
    turn_off_motor(R_REVERSE);
    turn_off_motor(L_REVERSE);
    
     lcd_4line();
     
     if(command[COMMAND_LENGTH] == COMMAND_CHAR_SYMBOL)
       receive_command(command + COMMAND_LENGTH);
  }
  // Right Command
   else if(find(CAR_RIGHT, temp_command))
  {
    display_1 = CLEAR_LINE;
    display_2 = command;
    display_3 = CLEAR_LINE;
    display_4 = CLEAR_LINE;
    
    lcd_BIG_mid();
    five_msec_delay(QUARTER_SECOND);
    Display_Process();
    
     uca0_transmit_message("SUCCESS", NO_OFFSET);    
     
    turn_on_motor(R_REVERSE);
    turn_on_motor(L_FORWARD);
    
    if(CH_TO_DIG(command[COMMAND_TIME_POS]) <= 9)
      five_msec_delay(SECOND * CH_TO_DIG(command[COMMAND_TIME_POS]) / COMMAND_TURN_RATIO);
    
    turn_off_motor(R_REVERSE);
    turn_off_motor(L_FORWARD);
    
     lcd_4line();
     
     if(command[COMMAND_LENGTH] == COMMAND_CHAR_SYMBOL)
       receive_command(command + COMMAND_LENGTH);
  }
  // Left Command
   else if(find(CAR_LEFT, temp_command))
  {
    display_1 = CLEAR_LINE;
    display_2 = command;
    display_3 = CLEAR_LINE;
    display_4 = CLEAR_LINE;
    
    lcd_BIG_mid();
    five_msec_delay(QUARTER_SECOND);
    Display_Process();
    
    uca0_transmit_message("SUCCESS", NO_OFFSET);    
     
    turn_on_motor(R_FORWARD);
    turn_on_motor(L_REVERSE);
    
     if(CH_TO_DIG(command[COMMAND_TIME_POS]) <= 9)
      five_msec_delay(SECOND * CH_TO_DIG(command[COMMAND_TIME_POS]) / COMMAND_TURN_RATIO);
    
    turn_off_motor(R_FORWARD);
    turn_off_motor(L_REVERSE);
    
     lcd_4line();
     
     if(command[COMMAND_LENGTH] == COMMAND_CHAR_SYMBOL)
       receive_command(command + COMMAND_LENGTH);
  }
  else if(find(CAR_LINE_FOLLOW, temp_command))
  {
    is_follow_running = is_follow_running ? FALSE : TRUE;
  }
}
