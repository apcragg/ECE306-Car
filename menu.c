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
    static u_int8 current_menu = MENU_WIFI;
    static u_int8 menu_pressed_count = START_ZERO;
    static char buffer[DISPLAY_LENGTH] = "0";
    static const u_int8 num_menu_options[NUM_MAIN_OPTIONS] = {5, 3, 4, 5, 1};
    static long int current_time = START_ZERO;
//------------------------------------------------------------------------------
 
//------------------------------------------------------------------------------
// Global Varriables
    char line_buffer1[DISPLAY_LENGTH];
    char line_buffer2[DISPLAY_LENGTH];
    char line_buffer3[DISPLAY_LENGTH];
    char line_buffer4[DISPLAY_LENGTH];
 //------------------------------------------------------------------------------
    
//------------------------------------------------------------------------------
// Static Const Data
    static char* const main_menu_options[NUM_LCD_LINES] = 
    {
      "1 Serial",
      "2 Line",
      "3 Shapes",
      " "
    };
    static char* const serial_menu_options[NUM_LCD_LINES] = 
    {
      "Set 9600",
      "Set 115200",
      " ",
      " "
    };
    static char* const line_menu_options[NUM_LCD_LINES] = 
    {
      "1 Blk Cal",
      "2 Wht Cal",
      "3 Basic",
      " "
    };
    static char* const shape_menu_options[NUM_LCD_LINES] = 
    {
      "1 TODO",
      "2 TODO",
      "3 TODO",
      "4 TODO"
    };    
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
  
  posL1 = DISPLAY_LINE_0;
  posL2 = DISPLAY_LINE_0;
  posL3 = DISPLAY_LINE_0;
  posL4 = DISPLAY_LINE_0;
    
  // TODO MOVE TO EACH OWN FUNCTION
  switch(current_menu)
  {    
    case MENU_MAIN:      
    display_1 = main_menu_options[ARR_POS_0];
    display_2 = main_menu_options[ARR_POS_1];
    display_3 = main_menu_options[ARR_POS_2];
    display_4 = main_menu_options[ARR_POS_3];
    break;
    case MENU_SERIAL:
    display_1 = serial_menu_options[ARR_POS_0];
    display_2 = serial_menu_options[ARR_POS_1];
    display_3 = " ";
    display_4 = " ";
    break;
    case MENU_LINE:
    display_1 = line_menu_options[ARR_POS_0];
    display_2 = line_menu_options[ARR_POS_1];
    display_3 = line_menu_options[ARR_POS_2];
    display_4 = buffer; 
       
    adc_val = (analog_read(ADC0) + analog_read(ADC1)) / DIVIDE_BY_TWO;
  
    buffer[ARR_POS_1] = '0';
    buffer[ARR_POS_2] = 'x';
    buffer[ARR_POS_3] = HEX_TO_CH((adc_val >> BYTE_SIZE  ) & NIBBLE);
    buffer[ARR_POS_4] = HEX_TO_CH((adc_val >> NIBBLE_SIZE) & NIBBLE);
    buffer[ARR_POS_5] = HEX_TO_CH((adc_val)                & NIBBLE);
    buffer[ARR_POS_6] = NULL_TERM;
    break;
    case MENU_SHAPES:
    display_1 = shape_menu_options[ARR_POS_0];
    display_2 = shape_menu_options[ARR_POS_1];
    display_3 = shape_menu_options[ARR_POS_2];
    display_4 = shape_menu_options[ARR_POS_3];
    break;
    case MENU_WIFI:
    if(system_time > current_time + SECOND * DOUBLE)
    {
      int i;
      uca1_transmit_message(GET_WIFI_IP_COMMAND, NO_OFFSET);
      five_msec_delay(QUARTER_SECOND / DIVIDE_BY_TWO); 
      BufferString a = uca1_read_buffer(FALSE);
      a.offset += IP_STATUS_OFFSET;
      
      display_1 = CLEAR_LINE;
      display_2 = " ip_addr";
      
      for(i = START_ZERO; i <= DISPLAY_LENGTH; i++)
      {
        line_buffer3[i] = ' ';
        line_buffer4[i] = ' ';
      }
      for(i = START_ZERO; i < ARR_POS_7; i++)
      {
        line_buffer3[ARR_POS_1 + i] = a.head[(a.offset + i) % BUFF_SIZE];
      }
      for(i = START_ZERO; i < ARR_POS_7; i++)
      {
        line_buffer4[ARR_POS_2 + i] = a.head[(a.offset + i + ARR_POS_7) % BUFF_SIZE];
      }
      
      display_3 = line_buffer3;
      display_4 = line_buffer4;
      
      current_time = system_time;
      /*int count = START_ZERO; 
      BufferString read_buff = uca1_read_buffer(FALSE);
      while(read_buff.head[(read_buff.offset + count) % BUFF_SIZE] != '\0')
      {
        if(find("ipaddr", 
                read_buff.head + ((read_buff.offset + count) % BUFF_SIZE)))
          display_1 = "FOUND IT!";
      }
      */
    }
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
          uca0_set_current_baud(BAUD_9600);
          uca0_transmit_message("Hello World", NO_OFFSET);
        }
        else if(menu_pressed_count == BAUD_115200)
        {
          uca0_set_current_baud(BAUD_115200);
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
      case MENU_WIFI:
        current_menu = MENU_MAIN;        
        menu_pressed_count = MENU_MAIN;
      break;
      default:
        current_menu = MENU_MAIN;
      break;
    }
  }
}
