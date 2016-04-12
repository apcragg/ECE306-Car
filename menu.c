//============================================================================//
// File Name : menu.c
//
// Description: This file contains the menu code.
//
// Author: Andrew Cragg
// Date: March 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//============================================================================//

#include "menu.h"

//------------------------------------------------------------------------------
// Local Varriables
    static u_int8 current_menu = MENU_SERIAL;
    static u_int8 menu_pressed_count = 0;
    static char buffer[11] = "0";
    static const u_int8 num_menu_options[4] = {4, 3, 4, 5};
//------------------------------------------------------------------------------
    
//------------------------------------------------------------------------------
// Static Const Data
    static char* const main_menu_options[4] = 
    {
      "1 Serial",
      "2 Line",
      "3 Shapes",
      " "
    };
    static char* const serial_menu_options[2] = 
    {
      "Set 9600",
      "Set 115200",
    };
    static char* const line_menu_options[3] = 
    {
      "1 Blk Cal",
      "2 Wht Cal",
      "3 Basic"
    };
    static char* const shape_menu_options[4] = 
    {
      "1 TODO",
      "2 TODO",
      "3 TODO",
      "4 TODO"
    };
    static char line_buffer1[11];
    static char line_buffer2[11];
    
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Function Name : update_menu
//
// Description: This function updates the menu given the current switches and
//              thumb wheel value.
// Arguements: void
// Returns:    void
//
// Author: Andrew Cragg
// Date: March 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void update_menu()
{
  int adc_val;
  char* read_buff;

  posL1 = DISPLAY_LINE_0;
  posL2 = DISPLAY_LINE_0;
  posL3 = DISPLAY_LINE_0;
  posL4 = DISPLAY_LINE_0;
    
  // TODO MOVE TO EACH OWN FUNCTION
  switch(current_menu)
  {    
    case MENU_MAIN:      
    display_1 = main_menu_options[0];
    display_2 = main_menu_options[1];
    display_3 = main_menu_options[2];
    display_4 = main_menu_options[3];
    break;
    case MENU_SERIAL:
    if(is_message_received())
    {
      int count = START_ZERO;
      read_buff = read_buffer(FALSE);
      line_buffer2[0] = NULL_TERM;
      while((count < LCD_LENGTH*2) && read_buff[count] != NULL_TERM)
      {       
        if(count < LCD_LENGTH)
        { 
          line_buffer1[count] = read_buff[count];
          line_buffer1[count+1] = NULL_TERM;
        }
        else line_buffer2[count - LCD_LENGTH] = read_buff[count];

        count++;
      }
      line_buffer2[count] = NULL_TERM;
      read_buffer(TRUE);
    }
    display_1 = serial_menu_options[0];
    display_2 = serial_menu_options[1];
    display_3 = line_buffer1;
    display_4 = line_buffer2;
    break;
    case MENU_LINE:
    display_1 = line_menu_options[0];
    display_2 = line_menu_options[1];
    display_3 = line_menu_options[2];
    display_4 = buffer; 
       
    adc_val = (analog_read(ADC0) + analog_read(ADC1)) / 2;
  
    buffer[1] = '0';
    buffer[2] = 'x';
    buffer[3] = HEX_TO_CH((adc_val >> 8) & NIBBLE);
    buffer[4] = HEX_TO_CH((adc_val >> 4) & NIBBLE);
    buffer[5] = HEX_TO_CH((adc_val >> 0) & NIBBLE);
    buffer[6] = NULL_TERM;
    break;
    case MENU_SHAPES:
    display_1 = shape_menu_options[0];
    display_2 = shape_menu_options[1];
    display_3 = shape_menu_options[2];
    display_4 = shape_menu_options[3];
    break;
    default:
      current_menu = MENU_MAIN;
    break;
  }
  
  switch(menu_pressed_count)
  {
    case DISPLAY_LINE_1: if((system_time % SECOND) > HALF_SECOND) 
      display_1 = " "; break;
    case DISPLAY_LINE_2: if((system_time % SECOND) > HALF_SECOND) 
      display_2 = " "; break;
    case DISPLAY_LINE_3: if((system_time % SECOND) > HALF_SECOND)
      display_3 = " "; break;
    case DISPLAY_LINE_4: if((system_time % SECOND) > HALF_SECOND) 
      display_4 = " "; break;
  } 
}

//------------------------------------------------------------------------------
// Function Name : handle_input
//
// Description: This function handles input from hardware/software switch 
//              presses.
// Arguements: void
// Returns:    void
//
// Author: Andrew Cragg
// Date: March 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void menu_handle_input(u_int8 sw_pressed)
{
  if(sw_pressed & SW_2)
  {
    menu_pressed_count = (menu_pressed_count + INCREMENT) 
                          % num_menu_options[current_menu];
  }
  else if(sw_pressed & SW1)
  {
    switch(current_menu)
    {
      case MENU_MAIN:
        if(menu_pressed_count == MENU_SERIAL)
        {
          current_menu = MENU_SERIAL;
          display_3 = " ";
        }
        else if(menu_pressed_count == MENU_LINE)
        {
          current_menu = MENU_LINE;
        }
        else if(menu_pressed_count == MENU_SHAPES)
        {
          current_menu = MENU_SHAPES;
        }
        menu_pressed_count = MENU_MAIN;
      break;
      case MENU_SERIAL:
        if(menu_pressed_count == BAUD_9600)
        {
          set_current_baud(BAUD_9600);
          transmit_message("Hello World");
        }
        else if(menu_pressed_count == BAUD_115200)
        {
          set_current_baud(BAUD_115200);
        }
        else
        {
          current_menu = MENU_MAIN;        
          menu_pressed_count = MENU_MAIN;
        }
      break;
      case MENU_LINE:
        if(menu_pressed_count == BLACK_VAL || menu_pressed_count == WHITE_VAL)
        {
          calibrate_sensors(menu_pressed_count);
        }
        else if(menu_pressed_count == RUN_BASIC_OPTION)
        {
          run_basic();
        }
        else
        {
          current_menu = MENU_MAIN;        
          menu_pressed_count = MENU_MAIN;
        }
      break;
       case MENU_SHAPES:
        {
          set_motor_speed(L_FORWARD, (int) (MAX_SPEED));
          set_motor_speed(R_FORWARD, (int) (MAX_SPEED));
  
          turn_on_motor(R_FORWARD);
          turn_on_motor(L_FORWARD);
          
          current_menu = MENU_MAIN;        
          menu_pressed_count = MENU_MAIN;
        }
      break;
      default:
        current_menu = MENU_MAIN;
      break;
    }
  }
}

