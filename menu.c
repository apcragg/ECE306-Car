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
    static int num_menu_options[4] = {4, 10, 10, 1};
    static int previous_value;
//------------------------------------------------------------------------------
    
//------------------------------------------------------------------------------
// Static Const Data
    static char* const main_menu_options[4] = 
    {
      "1 Resistors",
      "2 Shapes",
      "3 Songs",
      " "
    };
    static char* const resistor_codes[10] = 
    {
      "Black",
      "Brown",
      "Red",
      "Orange",
      "Yellow",
      "Green",
      "Blue",
      "Violet",
      "Grey",
      "White"
    };
    static char* const shape_menu_options[12] = 
    {
      " ",
      "Circle",
      "Square",
      "Triangle",
      "Octagon",
      "Pentagon",
      "Hexagon",
      "Cube",
      "Oval",
      "Sphere",
      "Cylinder",
      " "
    };
    
    static char* fight_song = "We're the Red and White from State And we know "
      "we are the best. A hand behind our back, We can take on all the rest. " 
      "Go to hell, Carolina. Devils and Deacs stand in line. "
      "The Red and White from N.C. State. Go State!          ";
    
    static char* red_white = "Red and White / White and Red / ";
    
    static int fight_song_start = START_ZERO;
    static char fight_song_buffer[DISPLAY_LENGTH];
    
    static int red_white_start = START_ZERO;
    static char red_white_buffer[DISPLAY_LENGTH];
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
  posL1 = DISPLAY_LINE_0;
  posL2 = DISPLAY_LINE_0;
  posL3 = DISPLAY_LINE_0;
  posL4 = DISPLAY_LINE_0;
    
  // TODO MOVE TO EACH OWN FUNCTION
  switch(current_menu)
  {        
    case MENU_MAIN:      
      update_main_menu();
    break;
    case MENU_RESISTORS:
      update_resistor_menu();
    break;
    case MENU_SHAPES:
      update_shape_menu();
    break;
    case MENU_SONG:
      update_song_menu();
    break;
    default:
      current_menu = MENU_MAIN;
    break;
  }
}

// Function Name : blink_menu_selection
//
// Description: This function blinks the current selection.
// Arguements: int          menu_selected
// Returns:    void
//
// Author: Andrew Cragg
// Date: April 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void blink_menu_selection(int menu_selected)
{
  switch(menu_selected % DISPLAY_LINE_4)
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
// Function Name : update_main_menu
//
// Description: This function updates the main menu with the 4 possible options
//              and blinks the current selection.
// Arguements: void
// Returns:    void
//
// Author: Andrew Cragg
// Date: April 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void update_main_menu()
{
  int menu_selection;
  menu_selection = analog_read(ADC3) / 
                   (MAX_ADC10 / (num_menu_options[current_menu]));
  
  display_1 = main_menu_options[DISPLAY_LINE_1 - OFF_BY_ONE];
  display_2 = main_menu_options[DISPLAY_LINE_2 - OFF_BY_ONE];
  display_3 = main_menu_options[DISPLAY_LINE_3 - OFF_BY_ONE];
  display_4 = main_menu_options[DISPLAY_LINE_4 - OFF_BY_ONE];
  
  blink_menu_selection(menu_selection);
  
  /*menu_selection = ((menu_selection % 4) == 0) ? 
                   menu_selection : menu_selection - (menu_selection % 4);*/
}

//------------------------------------------------------------------------------
// Function Name : update_resistor_menu
//
// Description: This function updates the resistor display and allows scrolling
//              through the various colors and codes.
// Arguements: void
// Returns:    void
//
// Author: Andrew Cragg
// Date: April 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void update_resistor_menu()
{
  int menu_selection;
  static char resistor_value[2] = {' ', '\0'};
  
  menu_selection = analog_read(ADC3) / 
                  (MAX_ADC10 / (num_menu_options[current_menu] - OFF_BY_ONE));
  resistor_value[0] = DIG_TO_CH(menu_selection);
  
  display_1 = "Color";
  display_2 = resistor_codes[menu_selection];
  display_3 = "Value";
  display_4 = resistor_value;
}

//------------------------------------------------------------------------------
// Function Name : update_shape_menu
//
// Description: This function updates the shape display and allows scrolling 
//              through the various shapes.
// Arguements: void
// Returns:    void
//
// Author: Andrew Cragg
// Date: April 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void update_shape_menu()
{
  int menu_selection;
  menu_selection = (analog_read(ADC3) / (MAX_ADC10 / 
                   (num_menu_options[current_menu]) - OFF_BY_ONE)) + OFF_BY_ONE;
  menu_selection = menu_selection > num_menu_options[current_menu] ? 
                   num_menu_options[current_menu] : menu_selection;
  
  display_1 = shape_menu_options[menu_selection - OFF_BY_ONE];
  display_2 = shape_menu_options[menu_selection];
  display_3 = shape_menu_options[menu_selection + OFF_BY_ONE];
}

//------------------------------------------------------------------------------
// Function Name : update_song_menu
//
// Description: This function updates the song display and scrolls through the
//              NC State fight song.
// Arguements: void
// Returns:    void
//
// Author: Andrew Cragg
// Date: April 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void update_song_menu()
{
  int i;
  int current_adc = analog_read(ADC3);
  if(current_adc > previous_value + SCROLL_FORWARD)
  {
    previous_value = current_adc;
    fight_song_start++;
    red_white_start++;
    
    if(fight_song_start > FIGHT_SONG_LENGTH) fight_song_start = START_ZERO;
    if(red_white_start > RED_WHITE_LENGTH) red_white_start = START_ZERO;
    
    for(i = START_ZERO; i < DISPLAY_LENGTH - OFF_BY_ONE; i++)
    {
      fight_song_buffer[i] = fight_song[i + fight_song_start];
      red_white_buffer[i] = red_white[(i + red_white_start) % RED_WHITE_LENGTH];
    }
    fight_song_buffer[DISPLAY_LENGTH - OFF_BY_ONE] = NULL_TERM;
    red_white_buffer[DISPLAY_LENGTH - OFF_BY_ONE] = NULL_TERM;
  }
  
   if(current_adc < previous_value - SCROLL_BACK)
   {
     previous_value = current_adc;
   }
  
  display_1 = red_white_buffer;
  display_2 = fight_song_buffer;
  display_3 = red_white_buffer;
  display_4 = " ";
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
  int menu_selection;
  menu_selection = analog_read(ADC3) / 
                  (MAX_ADC10 / num_menu_options[current_menu]);
  
  if(sw_pressed & SW_2)
  {
    current_menu = MENU_MAIN;        
    menu_selection = MENU_MAIN;
    lcd_4line(); 
  }
  else if(sw_pressed & SW1)
  {
    switch(current_menu)
    {
      case MENU_MAIN:
        if(menu_selection == MENU_RESISTORS)
        {
          current_menu = MENU_RESISTORS;
        }
        else if(menu_selection == MENU_SHAPES)
        {
          lcd_BIG_mid( ); 
          current_menu = MENU_SHAPES;
        }
        else if(menu_selection == MENU_SONG)
        {
          current_menu = MENU_SONG;
        }
        menu_selection = MENU_MAIN;
      break;
      case MENU_RESISTORS:
        if(menu_selection == MENU_MAIN)
        {
          current_menu = MENU_MAIN;        
          menu_selection = MENU_MAIN;
        }
      break;
      case MENU_SHAPES:
        if(menu_selection == MENU_MAIN)
        {
          current_menu = MENU_MAIN;        
          menu_selection = MENU_MAIN;
          lcd_4line(); 
        }
      break;
      case MENU_SONG:
        if(menu_selection == MENU_MAIN)
        {
          current_menu = MENU_MAIN;        
          menu_selection = MENU_MAIN;
        }
      break;
      default:
        current_menu = MENU_MAIN;
      break;
    }
  }
}

