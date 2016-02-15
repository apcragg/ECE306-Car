//============================================================================//
// File Name :display.c
//
// Description: This file contains the LCD display functions
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//============================================================================//

#include "macros.h"
#include "globals.h"
#include "functions.h"

//------------------------------------------------------------------------------
// Function Declarations
    void Init_Conditions(void);
    void Display_Process(void);
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Function Name : Init_Conditions
//
// Description: This function enables the hardware interupts and sets the 
//              display_x variables to the base address of the LCD char array
// Arguements: void
// Returns:    void
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void Init_Conditions(void){
//------------------------------------------------------------------------------
// Initializations Configurations
//------------------------------------------------------------------------------
// Interrupts are disabled by default, enable them. 
  enable_interrupts();
  display_1 = &display_line_1[LCD_BASE];
  display_2 = &display_line_2[LCD_BASE];
  display_3 = &display_line_3[LCD_BASE];
  display_4 = &display_line_4[LCD_BASE];

//------------------------------------------------------------------------------
}

//------------------------------------------------------------------------------
// Function Name : Display_Process
//
// Description: This function clears the current display and then sets the 
//              output text for each line of the LCD display
// Arguements: void
// Returns:    void
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void Display_Process(void){
  ClrDisplay();
  lcd_out(display_1, LCD_HOME_L1, posL1);
  lcd_out(display_2, LCD_HOME_L2, posL2);
  lcd_out(display_3, LCD_HOME_L3, posL3);
  lcd_out(display_4, LCD_HOME_L4, posL4);
}