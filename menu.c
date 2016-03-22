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
    static u_int8 current_menu = MENU_MAIN;
    static u_int8 menu_pressed_count = 0;
    static char buffer[2] = "0";
    static const u_int8 num_menu_options[3] = {3, 7, 3};
//------------------------------------------------------------------------------
    
//------------------------------------------------------------------------------
// Static Const Data
    static char* const main_menu_options[3] = 
    {
      "0. Main",
      "1. Shape",
      "2. List"
    };
    static char* const shape_menu_options[3] = 
    {
      "1. TODO",
      "2. Shape",
      "3. List"
    };
    static char* const line_menu_options[3] = 
    {
      "1. Blk Cal",
      "2. Wht Cal",
      "3. Basic"
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
  buffer[0] = DIG_TO_CH(menu_pressed_count);
  buffer[1] = NULL_TERM;
  
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
    display_4 = buffer;
    break;
    case MENU_SHAPES:
    display_1 = shape_menu_options[0];
    display_2 = shape_menu_options[1];
    display_3 = shape_menu_options[2];
    display_4 = buffer;
    break;
    case MENU_LINE:
    display_1 = line_menu_options[0];
    display_2 = line_menu_options[1];
    display_3 = line_menu_options[2];
    display_4 = buffer;
    break;
    default:
      current_menu = MENU_MAIN;
    break;
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
        if(menu_pressed_count == MENU_SHAPES)
        {
          current_menu = MENU_SHAPES;
        }
        else if(menu_pressed_count == MENU_LINE)
        {
          current_menu = MENU_LINE;
        }
        menu_pressed_count = MENU_MAIN;
      break;
      case MENU_SHAPES:
        {
          current_menu = MENU_MAIN;        
          menu_pressed_count = MENU_MAIN;
        }
      break;
      case MENU_LINE:
        if(menu_pressed_count == CAL_OPTION)
        {
          calibrate_sensors();
        }
        else if(menu_pressed_count == RUN_BASIC_OPTION)
        {
          ;
        }
        else
        {
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

