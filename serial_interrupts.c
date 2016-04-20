//============================================================================//
// File Name : serial_interrupts.c
//
// Description: This file contains the ADC ISR code
//
// Author: Andrew Cragg
// Date: March 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//============================================================================//

#include "msp430.h"
#include "macros.h"
#include "adc.h"
#include "globals.h"
#include "serial.h"

//------------------------------------------------------------------------------
// Module Scope Globals
//
//------------------------------------------------------------------------------

#pragma vector = USCI_A0_VECTOR
__interrupt void USCI_A0(void)
{
  switch(UCA0IV)
  {  
    case NO_INTERRUPT: // Vector 0 - no interrupt
    break;
    case RXIFG: // Vector 2 - RXIFG
      uca0_receive_char(UCA0RXBUF);
    break;
    case TXIFG: // Vector 4 – TXIFG
      uca0_transmit_char();
    break;
    default: 
    break;
  } 
}

#pragma vector = USCI_A1_VECTOR
__interrupt void USCI_A1(void)
{   
  switch(UCA1IV)
  {  
    case NO_INTERRUPT: // Vector 0 - no interrupt
    break;
    case RXIFG: // Vector 2 - RXIFG
      uca1_receive_char(UCA1RXBUF);
    break;
    case TXIFG: // Vector 4 – TXIFG
      uca1_transmit_char();
    break;
    default: 
    break;
  }
}