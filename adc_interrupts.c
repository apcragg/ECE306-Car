//============================================================================//
// File Name : adc_interrupts.c
//
// Description: This file contains the ADC ISR code
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//============================================================================//

#include "msp430.h"
#include "macros.h"
#include "adc.h"

#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
  if(ADC10IV | ADC10IV_ADC10IFG)
    set_conversion_flag(TRUE);
  
  ADC10IV = CLEAR_REGISTER;
}