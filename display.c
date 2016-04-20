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
// Local Variable
 
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

void display_buffer_string(BufferString string)
{
  int count = START_ZERO;
  line_buffer2[START_ZERO] = NULL_TERM;
  line_buffer3[START_ZERO] = NULL_TERM;
  line_buffer4[START_ZERO] = NULL_TERM;
   
  while((count < LCD_LENGTH * DISPLAY_LINE_4)
       && string.head[(count + string.offset) % BUFF_SIZE] != NULL_TERM
       && string.head[(count + string.offset) % BUFF_SIZE] != C_RETURN)
  {       
    if(count < LCD_LENGTH)
    { 
      line_buffer1[count] 
        = string.head[(count + string.offset) % BUFF_SIZE];
      line_buffer1[count + INCREMENT] = NULL_TERM;
    }
    else if(count < LCD_LENGTH * DISPLAY_LINE_2)
    {
      line_buffer2[count - LCD_LENGTH] 
        = string.head[(count + string.offset) % BUFF_SIZE];
      line_buffer2[count + INCREMENT] = NULL_TERM;
    }
    else if(count < LCD_LENGTH * DISPLAY_LINE_3)
    {
      line_buffer3[count - LCD_LENGTH * DISPLAY_LINE_2] 
        = string.head[(count + string.offset) % BUFF_SIZE];
      line_buffer3[count + INCREMENT] = NULL_TERM;
    }
    else if(count < LCD_LENGTH * DISPLAY_LINE_4)
    {
      line_buffer4[count - LCD_LENGTH * DISPLAY_LINE_3] 
        = string.head[(count + string.offset) % BUFF_SIZE];
      line_buffer3[count + INCREMENT] = NULL_TERM;
    }
      count++;
  }
  display_1 = line_buffer1;
  display_2 = line_buffer2;
  display_3 = line_buffer3;
  display_4 = line_buffer4;
}