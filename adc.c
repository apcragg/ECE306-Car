//============================================================================//
// File Name : adc.c
//
// Description: This file contains the ADC code
//
// Author: Andrew Cragg
// Date: March 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//============================================================================//

#include "adc.h"

//------------------------------------------------------------------------------
// Function Name : init_adc
//
// Description: This function initializes the ADC10 module for later use
// Arguements: void
// Returns:    void
//
// Author: Andrew Cragg
// Date: March 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void init_adc()
{
  ADC10CTL0 = CLEAR_REGISTER; // Clear ADC10CTL0
  ADC10CTL0 |= ADC10SHT_2; // 16 ADC clocks
  ADC10CTL0 &= ~ADC10MSC; // Single Sequence
  ADC10CTL0 |= ADC10ON; // ADC ON - Core Enabled

  ADC10CTL1 = CLEAR_REGISTER; // Clear ADC10CTL1
  ADC10CTL1 |= ADC10SHS_0; // ADC10SC bit
  ADC10CTL1 |= ADC10SHP; // SAMPCON signal sourced from sampling timer
  ADC10CTL1 &= ~ADC10ISSH; // The sample-input signal is not inverted.
  ADC10CTL1 |= ADC10DIV_0; // ADC10_B clock divider – Divide by 1.
  ADC10CTL1 |= ADC10SSEL_3; // SMCLK
  ADC10CTL1 |= ADC10CONSEQ_0; // Single-channel, single-conversion
  
  ADC10CTL2 = CLEAR_REGISTER; // Clear ADC10CTL2
  ADC10CTL2 |= ADC10DIV_0; // Pre-divide by 1
  ADC10CTL2 |= ADC10RES; // 10-bit resolution
  ADC10CTL2 &= ~ADC10DF; // Binary unsigned
  ADC10CTL2 &= ~ADC10SR; // supports up to approximately 200 ksps
  
  ADC10MCTL0 = CLEAR_REGISTER; // Clear ADC10MCTL0
  ADC10MCTL0 |= ADC10SREF_0; // V(R+) = AVCC and V(R-) = AVSS
  ADC10MCTL0 |= ADC10INCH_3; // Channel A3 Thumb Wheel
  ADC10IE |= ADC10IE0; // Enable ADC conversion complete interrupt

  //clk speed
  //resolution
  //mode
  //sample and hold
  //trigger mode
  //vref
}

//------------------------------------------------------------------------------
// Function Name : analog_read
//
// Description: TODO:
// Arguements: void
// Returns:    void
//
// Author: Andrew Cragg
// Date: March 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
int analog_read(int channel)
{
  int read_value = INVALID;
  
  ADC10CTL0 &= ~ADC10ENC;
  ADC10MCTL0 &= ~NIBBLE; // Clears Channel
  ADC10MCTL0 |= channel; // Sets Channel
  
  if(!(ADC10CTL1 & ADC10BUSY))
  {
    ADC10CTL0 |= ADC10ENC + ADC10SC;
    
    while(!conversion_flag); // Kill time until conversion complete
    
    read_value = ADC10MEM0;
  }
  
  conversion_flag = FALSE;
  
  return read_value;
}

//------------------------------------------------------------------------------
// Function Name : set_conversion_flag
//
// Description: Allows external interrupt to set the internal conversion flag
// Arguements: void
// Returns:    void
//
// Author: Andrew Cragg
// Date: March 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void set_conversion_flag(u_int8 set_flag)
 {
   conversion_flag = set_flag;
 }