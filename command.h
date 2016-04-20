#ifndef COMMANDS_H
#define COMMANDS_H

#include "macros.h"
#include "globals.h"
#include "msp430.h"
#include "serial.h"
#include "string.h"
#include "motor.h"
#include "functions.h"

//------------------------------------------------------------------------------
// Function Declarations
    void receive_command(char*);
//------------------------------------------------------------------------------

// Command Defines
#define COMMAND_LENGTH             (3)
#define COMMAND_TIME_POS           (2)
#define COMMAND_CHAR_SYMBOL        ('$')
#define COMMAND_TURN_RATIO         (8)

#define WIFI_COMMAND_SYMBOL        ("$")
#define LOST_WIFI_COMMAND_SYMBOL   ("Dis")
#define COMMAND_AKNOWLEDGE         ("~~")
#define AKNOWLEDGE_MESSAGE         ("Good News Everyone!\n\r")
#define SLOW_BAUD                  ("~S")
#define SLOW_BAUD_MESSAGE          ("Set 9600B\n\r")
#define SLOW_BAUD_COMMAND          ("AT+S.SCFG=console1_speed,9600\r")
#define FAST_BAUD                  ("~F")
#define FAST_BAUD_MESSAGE          ("Set 115200B\n\r")
#define FAST_BAUD_COMMAND          ("AT+S.SCFG=console1_speed,115200\r")
#define SAVE_COMMAND               ("AT&W\r")
#define RESET_COMMAND              ("AT+CFUN=1\r")
#define RESET_MESSAGE              ("IOT Device Reset")
#define G_MAC_COMMAND              ("AT+S.GCFG=nv_wifi_macaddr\r")
#define CONNECT_NCSU               ("~WIFI.C.NCSU")
#define CONNECT_NCSU_MESSAGE       ("Connecting to NCSU WiFi at SSID ")
#define SET_SSID_NCSU_COMMAND      ("AT+S.SSIDTXT=ncsu\r")
#define GET_SSID_NCSU_COMMAND      ("AT+S.SSIDTXT\r")
#define SET_HOST_NAME_COMMAND      ("AT+S.SCFG=ip_hostname,ECE306_01_AN\r")
#define GET_HOST_NAME_COMMAND      ("AT+S.GCFG=ip_hostname\r")
#define SET_PRIVACY_MODE_COMMAND   ("AT+S.SCFG=wifi_priv_mode,0\r")
#define GET_PRIVACY_MODE_COMMAND   ("AT+S.GCFG=wifi_priv_mode\r")
#define SET_NETWORK_MODE_COMMAND   ("AT+S.SCFG=wifi_mode,1\r")
#define GET_NETWORK_MODE_COMMAND   ("AT+S.GCFG=wifi_mode\r")
#define GET_WIFI_STATUS            ("~WIFI.S")
#define GET_WIFI_STATUS_COMMAND    ("AT+S.STS\r")
#define GET_WIFI_IP                ("~WIFI.IP")
#define GET_WIFI_IP_COMMAND        ("AT+S.STS=ip_ipaddr\r")
#define CAR_FORWARD                ("$F")
#define CAR_BACKWARD               ("$B")
#define CAR_RIGHT                  ("$R")
#define CAR_LEFT                   ("$L")

#endif