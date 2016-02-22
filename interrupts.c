//============================================================================//
// File Name : shapes.c
//
// Description: This file contains the  shape driving code
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//============================================================================//

#include "msp430.h"
#include "macros.h"

#pragma vector = TIMER1_B1_VECTOR
__interrupt void timer_B1_CCR0_interupt(void)
{
  TB1CCTL1 &= ~TAxCTL_IFG;        // clears the interupt flag
  TB1CCTL2 &= ~TAxCTL_IFG;        // clears the interupt flag
}

#pragma vector = TIMER2_B1_VECTOR
__interrupt void timer_B2_CCR0_interupt(void)
{
  TB2CCTL1 &= ~TAxCTL_IFG;        // clears the interupt flag
  TB2CCTL2 &= ~TAxCTL_IFG;        // clears the interupt flag
}

#pragma vector = TIMER1_A1_VECTOR
__interrupt void timer_A1_CCR1_interupt(void)
{
  TA1CCTL1 &= ~CCIFG;                   // clears the interupt flag
  TA1CCTL1 &= ~CCIE;
  P4IE |= SW_1 | SW_2; 
}

#pragma vector = TIMER1_A0_VECTOR
__interrupt void timer_A1_CTL_interupt(void)
{
  TA1CTL &= ~CCIFG;                   // clears the interupt flag
}