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
#include  "timers.h"
#include  "ports.h"

// Global Variables
volatile unsigned char control_state[CNTL_STATE_INDEX];
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

void setup_pwm(void);

void main(void){
//------------------------------------------------------------------------------
// Main Program
// This is the main routine for the program. Execution of code starts here.
// The operating system is Back Ground Fore Ground.
// 
//------------------------------------------------------------------------------
  
  init_ports();                            
  Init_Clocks();                            
  Init_Conditions();                     
  init_timers();                            
  five_msec_delay(QUARTER_SECOND);                      
  Init_LCD();  
  setup_sw_debounce();
  
  WDTCTL = WDTPW + WDTHOLD;
  
  setup_pwm();
  
  set_motor_speed(R_FORWARD, PWM_RES);
  set_motor_speed(L_FORWARD, PWM_RES);
  
  display_1 = "NCSU";
  posL1 = DISPLAY_LINE_3;
  display_2 = "WOLFPACK";
  posL2 = DISPLAY_LINE_1;
  display_3 = "ECE306";
  posL3 = DISPLAY_LINE_2;
  display_4 = "Andrew C";
  posL4 = DISPLAY_LINE_1;
  Display_Process();

  char one_time;                                // Timer boolean
  unsigned int      time_sequence  = START_VAL; // counter for switch loop
  unsigned int previous_count = START_VAL;      // automatic variable for
                                                // comparing timer_count
  
//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
while(ALWAYS) {                            // Can the Operating system run
  switch(time_sequence){
    case SECOND_AND_A_QUARTER:              // 1250 msec  
      if(one_time){
        one_time = FALSE;
      }
      time_sequence = FALSE;                    
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
      Display_Process();
      break;                                
    default: break; 
  }
  Switches_Process(FALSE);                 // Check for switch state change 
  
  if(time_sequence > SECOND_AND_A_QUARTER)
    time_sequence = START_VAL;
  
  unsigned int current_timer_count = get_timer_count();
  
  if(current_timer_count > previous_count)
  {
    previous_count = current_timer_count;
    time_sequence++;
  } 
 }
//------------------------------------------------------------------------------
}

void setup_pwm()
{ 
    // R_FORWARD on P3.4
    init_pwm(&TB1CTL);
  
    set_pwm_resolution(&TB1CCR0, PWM_RES);
    set_pwm_value(&TB1CCR1, PWM_RES / 2);
    set_pwm_output(&TB1CCTL1);
    
    P3DIR |= R_FORWARD;
    P3SEL0 |= R_FORWARD;
    P3SEL1 &= ~R_FORWARD;   
    
    start_pwm(&TB1CTL);
    
    // L_FORWARD on P3.6
    init_pwm(&TB2CTL);
  
    set_pwm_resolution(&TB2CCR0, PWM_RES);
    set_pwm_value(&TB2CCR1, PWM_RES / 2);
    set_pwm_output(&TB2CCTL1);
    
    P3DIR |= L_FORWARD;
    P3SEL0 |= L_FORWARD;
    P3SEL1 &= ~L_FORWARD;   
    
    start_pwm(&TB2CTL);
    
    // R_REVERSE on P3.5  
    set_pwm_value(&TB1CCR2, PWM_RES / 2);
    set_pwm_output(&TB1CCTL2);
    
    P3DIR |= R_REVERSE;
    P3SEL0 |= R_REVERSE;
    P3SEL1 &= ~R_REVERSE;   
    
    // L_REVERSE on P3.7 
    set_pwm_value(&TB2CCR2, PWM_RES / 2);
    set_pwm_output(&TB2CCTL2);
    
    P3DIR |= L_REVERSE;
    P3SEL0 |= L_REVERSE;
    P3SEL1 &= ~L_REVERSE;   
}

