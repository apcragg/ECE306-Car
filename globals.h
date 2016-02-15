//============================================================================//
// File Name : globals.h
//
// Description: This file contains the global variable extern defenitions
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//============================================================================//

// Global Variables 
extern char display_line_1[DISPLAY_LENGTH];
extern char display_line_2[DISPLAY_LENGTH];
extern char display_line_3[DISPLAY_LENGTH];
extern char display_line_4[DISPLAY_LENGTH];
extern char *display_1;
extern char *display_2;
extern char *display_3;
extern char *display_4;
extern char posL1;
extern char posL2;
extern char posL3;
extern char posL4;
extern volatile unsigned char control_state[CNTL_STATE_INDEX];
extern volatile unsigned int Time_Sequence;
extern char led_smclk;
extern volatile char one_time;
extern volatile unsigned int five_msec_count;
extern char size_count;
extern char big;