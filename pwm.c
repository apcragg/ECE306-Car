//============================================================================//
// File Name : pwm.c
//
// Description: This file contains the pulse width modulaition code
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//============================================================================//

#include "pwm.h"
#include "msp430.h"
#include "macros.h"

//------------------------------------------------------------------------------
// Function Name : init_pwm
//
// Description: This function sets up the passed Timer control register for
//              PWM operation
// Arguements: unsigned short volatile*         TxxCTL
// Returns:    void
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void inline init_pwm(unsigned short volatile* TxxCTL)
{
    *TxxCTL &= ~TIMER_STOP; 
    *TxxCTL &= ~TBIE;
    *TxxCTL |= TASSEL_2;
    //*TxxCTL |= TIMER_DIVIDE;
}

//------------------------------------------------------------------------------
// Function Name : set_pwm_resolution
//
// Description: This function sets the PWM resolution to the passed Timer 
//              control register. The resolution is how many PWM steps are
//              possible. The frequency of the PWM is CLK_F / resolution
// Arguements: unsigned short volatile*         TxxCTL
//             unsigned int                     resolution
// Returns:    void
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void inline set_pwm_resolution(unsigned short volatile* TxxCCR0, unsigned int resolution)
{
    *TxxCCR0 = resolution;
}

//------------------------------------------------------------------------------
// Function Name : set_pwm_value
//
// Description: This function sets the PWM value to the passed control register.
//              The PWM duty cycle is 100% - (value / reosultion) * 100%
//              This inverted nature is due to a lack of OUT_MOD_SET_RES
//              on the CCR0 register
//              possible. The frequency of the PWM is CLK_F / resolution
// Arguements: unsigned short volatile*         TxxCTL
//             unsigned int                     value
// Returns:    void
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void inline set_pwm_value(unsigned short volatile* TxxCCRn, unsigned int value)
{
    *TxxCCRn = value;
}

//------------------------------------------------------------------------------
// Function Name : set_pwm_output
//
// Description: This function sets the PWM output from the passed control
//              register. Disables interrupts from this seconadry register.
// Arguements: unsigned short volatile*         TxxCCTLn
// Returns:    void
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void inline set_pwm_output(unsigned short volatile* TxxCCTLn)
{
    *TxxCCTLn &= CLEAR_REGISTER;
    *TxxCCTLn &= ~COMPARE_MODE;
    *TxxCCTLn &= ~CCIE;
}

//------------------------------------------------------------------------------
// Function Name : start_pwm
//
// Description: This function starts the PWM on the passed register on up mode.
// Arguements: unsigned short volatile*         TxxCTL
// Returns:    void
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void inline start_pwm(unsigned short volatile* TxxCTL)
{
   *TxxCTL |= TIMER_UP;
}

//------------------------------------------------------------------------------
// Function Name : disable_pwm
//
// Description: This function stops the PWM on the passed register.
// Arguements: unsigned short volatile*         TxxCTL
// Returns:    void
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void inline disable_pwm(unsigned short volatile* TxxCCTLn)
{
   *TxxCCTLn &= ~OUTMOD;
}

//------------------------------------------------------------------------------
// Function Name : enable
//
// Description: This function enables the PWM on the passed register.
// Arguements: unsigned short volatile*         TxxCTL
// Returns:    void
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void inline enable_pwm(unsigned short volatile* TxxCCTLn)
{
   *TxxCCTLn &= ~CCIFG;
   *TxxCCTLn &= ~CCIE;
   *TxxCCTLn |= OUTMOD_RES_SET;
}