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
// Local Varriables
    static int adc_val[4];
//------------------------------------------------------------------------------

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
  // TODO: Turn on LED, no delay needed as rise time is ~900ns per the 
  // data sheet and at 8Mhz that is < 7 1 cycle instructions
  
  int read_value = INVALID;
  
  ADC10CTL0 &= ~ADC10ENC;
  ADC10MCTL0 &= ~NIBBLE; // Clears Channel
  ADC10MCTL0 |= channel; // Sets Channel
  
  // Force completes a conversion and returns the value
  if(!(ADC10CTL1 & ADC10BUSY))
  {
    ADC10CTL0 |= ADC10ENC + ADC10SC;
    
    while(!conversion_flag); // Kill time until conversion complete
    
    read_value = ADC10MEM0;
  }
  else                                  
  {
    while(ADC10CTL1 & ADC10BUSY); // Kill time until ADC ready
    
    ADC10CTL0 |= ADC10ENC + ADC10SC;
    
    while(!conversion_flag); // Kill time until conversion complete
    
    read_value = ADC10MEM0;
  }
  
  conversion_flag = FALSE;
  
  return read_value;
}

//------------------------------------------------------------------------------
// Function Name : set_adc_val
//
// Description: Retrieves the internal ADC value of the requested channel
// Arguements: channel          ADC channel the value is to come from
// Returns:                     The requested ADC value
//
// Author: Andrew Cragg
// Date: March 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
int get_adc_val(u_int8 channel)
{
  return adc_val[channel];
}

//------------------------------------------------------------------------------
// Function Name : set_adc_val
//
// Description: Sets the internal ADC data to the value read from the ADC
// Arguements: channel          ADC channel the value came from
//             value            ADC value to store
// Returns:    void
//
// Author: Andrew Cragg
// Date: March 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void set_adc_val(u_int8 channel, int value)
{
  adc_val[channel] = value;
}

//------------------------------------------------------------------------------
// Function Name : set_conversion_flag
//
// Description: Allows external interrupt to set the internal conversion flag
// Arguements: set_flag         boolean value for flag to be set to
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