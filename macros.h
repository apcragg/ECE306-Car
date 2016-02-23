#ifndef MACROS_H
#define MACROS_H

//============================================================================//
// File Name : macros.h
//
// Description: This file contains he macro define defentions
//
// Author: Andrew Cragg
// Date: Feb 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//============================================================================//


typedef unsigned char u_int8;
typedef unsigned char bool;

#include "msp430.h"

// Required defines
// In the event the universe no longer exists, this bit will reset
#define ALWAYS                  (1)
#define CNTL_STATE_INDEX        (3) // Control States
#define LED                     (0xFF) // Use LED's
#define CONTROL                 (0xFE) // USe Control Logic
#define CNTL_STATE_INDEX        (3)
#define false                   (0)
#define true                    (1)
#define UINT_16_MAX             (0xFFFF)
#define PI                      (3.1415) // PI


// Helper macros
#define DIG_TO_CH(D)            ((D)+0x30) // Converts a digit to an ASCII char

// LCD
#define LCD_HOME_L1	        (0x80)
#define LCD_HOME_L2         	(0xA0)
#define LCD_HOME_L3         	(0xC0)
#define LCD_HOME_L4         	(0xE0)
#define LCD_BASE                (0x00)
#define NULL_TERM               (0x00)

//Timeing Values
#define FALSE                   (0x00)
#define TRUE                    (0x01)
#define START_VAL               (0x00)
#define SIZE_CHANGE_TIME        (5)
#define TIMER_COUNT             (1000)
#define OFF_BY_ONE_OFFSET       (1)
#define QUARTER_SECOND          (50)
#define HALF_SECOND             (100)
#define THREE_QUARTER_SECOND    (150)
#define SECOND                  (200)
#define SECOND_AND_A_QUARTER    (250)

//Display Values
#define DISPLAY_LENGTH          (11)
#define DISPLAY_LINE_1          (1)
#define DISPLAY_LINE_2          (2)
#define DISPLAY_LINE_3          (3)
#define DISPLAY_LINE_4          (4)

//------------------------------------------------------------------------------
// Port Macros
//------------------------------------------------------------------------------

// General Purpose Things
#define GPIO_SEL                (0x00) // Sets Port as I/O
#define CLEAR_REGISTER          (0x0000) // Clears registers with 0x00

// Port 1
#define V_DETECT_R              (0x01) // Port 1.0
#define V_DETECT_L              (0x02) // Port 1.1
#define IR_LED                  (0x04) // Port 1.2
#define V_THUMB                 (0x08) // Port 1.3
#define SPI_CS_LCD              (0x10) // Port 1.4
#define RESET_LCD               (0x20) // Port 1.5
#define SPI_SIMO                (0x40) // Port 1.6
#define SPI_SOMI                (0x80) // Port 1.7

// Port 2
#define USB_TDX                 (0x01) // Port 2.0
#define USB_RDX                 (0x02) // Port 2.1
#define SPI_SCK                 (0x04) // Port 2.2
#define UNDEF_1                 (0x08) // Port 2.3
#define UNDEF_2                 (0x10) // Port 2.4
#define CPU_TXD                 (0x20) // Port 2.5
#define CPU_RXD                 (0x40) // Port 2.6
#define UNDEF_3                 (0x80) // Port 2.7

// Port 3
#define ACCEL_X                 (0x01) // Port 3.0
#define ACCEL_Y                 (0x02) // Port 3.1
#define ACCEL_Z                 (0x04) // Port 3.2
#define LCD_BACKLIGHT           (0x08) // Port 3.3
#define R_FORWARD               (0x10) // Port 3.4
#define R_REVERSE               (0x20) // Port 3.5
#define L_FORWARD               (0x40) // Port 3.6
#define L_REVERSE               (0x80) // Port 3.7

// Port 4
#define SW1                     (0x01) // Port 4.0
#define SW2                     (0x02) // Port 4.1

// Port J
#define IOT_WAKEUP              (0x01) // Port J.0
#define IOT_FACTORY             (0x02) // Port J.1
#define IOT_STA_MINIAP          (0x04) // Port J.2
#define IOT_RESET               (0x08) // Port J.3

// Port Direction
#define GPIO_IN                 (0x00) // Value for full Port GPIO input
#define GPIO_OUT                (0xFF) // Value for full Port GPIO output

//------------------------------------------------------------------------------
// Other macros
//------------------------------------------------------------------------------

//pwm things
#define NUM_A_TIMERS            (7)    // Number of timer registers on Timer A
#define TIMER_A0                (0x00) // Timer A0
#define TIMER_A1                (0x01) // Timer A1
#define TIMER_A2                (0x02) // Timer A2
#define TIMER_A3                (0x03) // Timer A3
#define TIMER_A4                (0x04) // Timer A4
#define TIMER_A5                (0x05) // Timer A5
#define TIMER_A6                (0x06) // Timer A6
#define PWM_RES                 (4096) // PWM resolution

// Motor constants
#define MOTOR_ADJ_FAC           (0.955f) // Left motor compensation
#define MAX_SPEED               (PWM_RES)
#define MOTOR_SPD_OFF           (0x00) // Motor speed of zero

// Shape Constants
#define NUM_SHAPES              (6)    // Number of possible shapes
#define INCREMENT               (1)    // Shape counter increment
#define DIR_LEFT                (0x00) // Port side
#define DIR_RIGHT               (0x01) // Starboard side
#define NUM_TRI_PTS             (3)    // Number of points in a triangle
#define R_LEN_COMP              (1.30f)// Right motor durration compensation
#define BATT_COMP               (4.99f / 4.88f) // current battery level
#define UN_COMP                 (1.0f) // No adjustment compensation factor

//Switch things
#define SW_1                    (0x01) // Switch 1
#define SW_2                    (0x02) // Switch 2
#define TA1_CLK_F               (10000)// Timer A0 frequency in hz
#define ONE_MSEC                (1000) // Number of msec in a second
#define PRESSED_DEBOUNCE        (35)   // Debounce time for switch press
#define RELEASED_DEBOUNCE       (175)  // Debounce time for switch press

//Timer things
#define TA_CTL_BASE             (TA0CTL)
#define TA_CCR0_BASE            (TA0CCR0)
#define TIMER_STOP              (0x0030) //Stop mask for timer       Bits 5-4 11
#define TIMER_UP                (0x0010) //Continuous mask for timer Bits 5-4 01
#define TIMER_CONTINUOUS        (0x0020) //Continuous mask for timer Bits 5-4 10

#define CAPTURE_MODE            (0xC000) // Timer_A capture mode
#define NO_CAPTURE              (0x0000) // No capture bit mask
#define COMPARE_MODE            (0x0100) // Compare mode
#define OUTMOD                  (0x0070) // Outmod bit mask
#define OUTMOD_RES_SET          (0x0070) // Outmod Reset/Set mode
#define OUTMOD_SET_RES          (0x0030) // Outmod Set/Reset mode
#define OUTMOD_TOGGLE           (0x0040) // Outmod toggle
#define TIMER_DIVIDE            (0x00C0) // Timer division
#define TAxCTL_IFG              (0x0001) // Timer CTL interupt flag
#define Px_IFG                  (0x0001) // Port interrupt flag

#endif