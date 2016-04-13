//============================================================================//
// File Name : ports.c
//
// Description: This file contains the Initialization for all port pins
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//============================================================================//

#include "ports.h"

//------------------------------------------------------------------------------
// Function Name : Init_Ports
//
// Description: This function calls the initialization functions for each
//              Port on the MSP430
// Arguements: void
// Returns:    void
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void init_ports(void)
{
    init_port_1(); 
    init_port_2(); 
    init_port_3(); 
    init_port_4(); 
    init_port_J(); 
}

//------------------------------------------------------------------------------
// Function Name : Init_Port_1
//
// Description: This function initializes Port_1 on the MSP430
//              Sets the Pin Modes, Directions, and Initial Coniditons
// Arguements: void
// Returns:    void
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void init_port_1(void)
{
  //Sets base Port ain a full GPIO Input state
  P1SEL0 = GPIO_SEL;
  P1SEL1 = GPIO_SEL;
  P1DIR = GPIO_IN;
  
  //Set Port Functions other than GPIO
  P1SEL0 |= V_DETECT_R;
  P1SEL1 |= V_DETECT_R;
  P1SEL0 |= V_DETECT_L;
  P1SEL1 |= V_DETECT_L;
  P1SEL0 |= V_THUMB;
  P1SEL1 |= V_THUMB;
  P1SEL0 &= ~SPI_SIMO;
  P1SEL1 |= SPI_SIMO;
  P1SEL0 &= ~SPI_SOMI;
  P1SEL1 |= SPI_SOMI;
  
  //Set Port Directions Other than Input
  P1DIR |= IR_LED;
  P1DIR |= SPI_CS_LCD;
  P1DIR |= RESET_LCD;
    
  //Set Port Output States
  P1OUT &= ~IR_LED;
  P1OUT |= SPI_CS_LCD;
  P1OUT &= ~RESET_LCD;
  
  //Set Port Pullup Resistors
  P1REN |= SPI_SOMI;
}

//------------------------------------------------------------------------------
// Function Name : Init_Port_2
//
// Description: This function initializes Port_1 on the MSP430
//              Sets the Pin Modes, Directions, and Initial Coniditons
// Arguements: void
// Returns:    void
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void init_port_2(void)
{
  //Sets base Port ain a full GPIO Input state
  P2SEL0 = GPIO_SEL;
  P2SEL1 = GPIO_SEL;
  P2DIR = GPIO_IN;
  
  //Set Port Functions other than GPIO
  P2SEL0 &= ~USB_TDX;
  P2SEL1 |= USB_TDX;
  P2SEL0 &= ~USB_RDX;
  P2SEL1 |= USB_RDX;
  P2SEL0 &= ~SPI_SCK;
  P2SEL1 |= SPI_SCK;
  P2SEL0 &= ~CPU_TXD;
  P2SEL1 |= CPU_TXD;
  P2SEL0 &= ~CPU_RXD;
  P2SEL1 |= CPU_RXD;
  
  //Set Port Directions Other than Input
  P2DIR |= UNDEF_1;
  P2DIR |= UNDEF_2;
  P2DIR |= UNDEF_3;
    
  //Set Port Output States
  P2OUT |= SPI_SCK;
  P2OUT &= ~UNDEF_1;
  P2OUT &= ~UNDEF_2;
  P2OUT &= ~UNDEF_3;
  
  //Set Port Pullup Resistors
  P2REN &= ~UNDEF_1;
  P2REN &= ~UNDEF_2;
  P2REN &= ~UNDEF_3;
}

//------------------------------------------------------------------------------
// Function Name : Init_Port_3
//
// Description: This function initializes Port_1 on the MSP430
//              Sets the Pin Modes, Directions, and Initial Coniditons
// Arguements: void
// Returns:    void
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void init_port_3(void)
{
  //Sets base Port ain a full GPIO Input state
  P3SEL0 = GPIO_SEL;
  P3SEL1 = GPIO_SEL;
  P3DIR = GPIO_IN;
  
  //Set Port Functions other than GPIO
  // n/a for Port 3
  
  //Set Port Directions Other than Input
  P3DIR |= LCD_BACKLIGHT;
  P3DIR |= R_FORWARD;
  P3DIR |= R_REVERSE;
  P3DIR |= L_FORWARD;
  P3DIR |= L_REVERSE;
    
  //Set Port Output States other than Zero
  P3OUT &= ~LCD_BACKLIGHT;
  P3OUT &= ~R_FORWARD;
  P3OUT &= ~R_REVERSE;
  P3OUT &= ~L_FORWARD;
  P3OUT &= ~L_REVERSE;
  
  //Set Port Pullup Resistors
  P3REN &= ~ACCEL_X;
  P3REN &= ~ACCEL_Y;
  P3REN &= ~ACCEL_Z;
}

//------------------------------------------------------------------------------
// Function Name : Init_Port_4
//
// Description: This function initializes Port_1 on the MSP430
//              Sets the Pin Modes, Directions, and Initial Coniditons
// Arguements: void
// Returns:    void
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void init_port_4(void)
{
   //Sets base Port ain a full GPIO Input state
  P4SEL0 = GPIO_SEL;
  P4SEL1 = GPIO_SEL;
  P4DIR = GPIO_IN;
  
  //Set Port Functions other than GPIO
  // n/a for Port 4
  
  //Set Port Directions Other than Input
  // n/a for Port 4
    
  //Set Port Output States
  P4OUT |= SW1;
  P4OUT |= SW2;

  
  //Set Port Pullup Resistors
  P4REN |= SW1;
  P4REN |= SW2;
}

//------------------------------------------------------------------------------
// Function Name : Init_Port_J
//
// Description: This function initializes Port_J on the MSP430
//              Sets the Pin Modes, Directions, and Initial Coniditons
// Arguements: void
// Returns:    void
//
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void init_port_J(void)
{
  //Sets base Port ain a full GPIO Input state
  PJSEL0 = GPIO_SEL;
  PJSEL1 = GPIO_SEL;
  PJDIR = GPIO_IN;
  
  //Set Port Functions other than GPIO
  // n/a for Port 3
  
  //Set Port Directions Other than Input
  PJDIR |= IOT_WAKEUP;
  PJDIR |= IOT_FACTORY;
  PJDIR |= IOT_STA_MINIAP;
  PJDIR |= IOT_RESET;
    
  //Set Port Output States other than Zero
  PJOUT &= ~IOT_WAKEUP;
  PJOUT &= ~IOT_FACTORY;
  PJOUT |= IOT_STA_MINIAP;
  PJOUT &= ~IOT_RESET;
  
  //Set Port Pullup Resistors
  // n/a for Port J
}


