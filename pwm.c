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

void inline init_pwm(unsigned short volatile* TxxCTL)
{
    *TxxCTL &= ~TIMER_STOP; 
    *TxxCTL |= TBIE;
    *TxxCTL |= TASSEL_2;
    //*TxxCTL |= TIMER_DIVIDE;
}

void inline set_pwm_resolution(unsigned short volatile* TxxCCR0, unsigned int resolution)
{
    *TxxCCR0 = resolution;
}

void inline set_pwm_value(unsigned short volatile* TxxCCRn, unsigned int value)
{
    *TxxCCRn = value;
}

void inline set_pwm_output(unsigned short volatile* TxxCCTLn)
{
    *TxxCCTLn &= CLEAR_REGISTER;
    *TxxCCTLn &= ~COMPARE_MODE;
    *TxxCCTLn |= OUTMOD_RES_SET;
    *TxxCCTLn &= ~CCIE;
}

void inline start_pwm(unsigned short volatile* TxxCTL)
{
   *TxxCTL |= TIMER_UP;
}