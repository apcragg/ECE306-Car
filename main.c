//------------------------------------------------------------------------------
//
//  Description: This file contains the Main Routine - "While" Operating System
//
//
//  Jim Carlson
//  Jan 2016
//  Built with IAR Embedded Workbench Version: V7.3.1.3987 (6.40.1)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"
#include  "pwm.h"
#include  "motor.h"
#include  "switch.h"

void setup_pwm();

// Global Variables
volatile unsigned char control_state[CNTL_STATE_INDEX];
volatile unsigned int Time_Sequence;
char led_smclk;
volatile char one_time;
volatile unsigned int five_msec_count;
extern char display_line_1[11];
extern char display_line_2[11];
extern char display_line_3[11];
extern char display_line_4[11];
extern char *display_1;
extern char *display_2;
extern char *display_3;
extern char *display_4;
char posL1;
char posL2;
char posL3;
char posL4;
char size_count;
char big;

void main(void){
//------------------------------------------------------------------------------
// Main Program
// This is the main routine for the program. Execution of code starts here.
// The operating system is Back Ground Fore Ground.
// 
//------------------------------------------------------------------------------
  
  Init_Ports();                            
  Init_Clocks();                            
  Init_Conditions();
  Time_Sequence = START_VAL;                        
  Init_Timers();                            
  five_msec_sleep(QUARTER_SECOND);                      
  Init_LCD();  
  setup_sw_debounce();
  
  WDTCTL = WDTPW + WDTHOLD;
  
  setup_pwm();
  
  set_motor_speed(R_FORWARD, 4096);
  set_motor_speed(L_FORWARD, 4096);
  
//             1234567890
  display_1 = "NCSU";
  posL1 = DISPLAY_LINE_3;
  display_2 = "WOLFPACK";
  posL2 = DISPLAY_LINE_1;
  display_3 = "ECE306";
  posL3 = DISPLAY_LINE_2;
  display_4 = "Andrew C";
  posL4 = DISPLAY_LINE_1;
  big = 0;
  Display_Process();

  
//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
while(ALWAYS) {                            // Can the Operating system run
  switch(Time_Sequence){
    case SECOND_AND_A_QUARTER:              // 1250 msec  
      if(one_time){
        one_time = FALSE;
      }
      Time_Sequence = FALSE;                    
    case SECOND:                            // 1000 msec  
      if(one_time){
        one_time = FALSE;
      }
    case THREE_QUARTER_SECOND:              // 750 msec  
      if(one_time){
        one_time = FALSE;
      }
    case HALF_SECOND:                       // 500 msec  
      if(one_time){
        one_time = FALSE;
      }
    case  QUARTER_SECOND:                   // 250 msec  
      if(one_time){
        one_time = FALSE;
      }
      size_count++;
      if(size_count > SIZE_CHANGE_TIME){
        size_count = FALSE;
        if(big){
          lcd_BIG_mid();
          big = FALSE;
        }else{
          lcd_4line();
          big = TRUE;
        }
      }
        Display_Process();
      break;                                // 
    default: break; 
  }
  //Switches_Process();                       // Check for switch state change 
  if(Time_Sequence > SECOND_AND_A_QUARTER){
    Time_Sequence = START_VAL;
  }

 }
//------------------------------------------------------------------------------
}

void setup_pwm()
{
  
    // R_FORWARD on P3.4
    init_pwm(&TB1CTL);
  
    set_pwm_resolution(&TB1CCR0, PWM_RES);
    set_pwm_value(&TB1CCR1, 2048);
    set_pwm_output(&TB1CCTL1);
    
    P3DIR |= R_FORWARD;
    P3SEL0 |= R_FORWARD;
    P3SEL1 &= ~R_FORWARD;   
    
    start_pwm(&TB1CTL);
    
    // L_FORWARD on P3.6
    init_pwm(&TB2CTL);
  
    set_pwm_resolution(&TB2CCR0, PWM_RES);
    set_pwm_value(&TB2CCR1, 2048);
    set_pwm_output(&TB2CCTL1);
    
    P3DIR |= L_FORWARD;
    P3SEL0 |= L_FORWARD;
    P3SEL1 &= ~L_FORWARD;   
    
    start_pwm(&TB2CTL);
}

#pragma vector = TIMER1_B1_VECTOR
__interrupt void timer_B1_CCR0_interupt(void)
{
  TB1CTL &= ~TAxCTL_IFG;        // clears the interupt flag
}

#pragma vector = TIMER2_B1_VECTOR
__interrupt void timer_B2_CCR0_interupt(void)
{
  TB2CTL &= ~TAxCTL_IFG;        // clears the interupt flag
}


