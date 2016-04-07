//============================================================================//
// File Name : serial.c
//
// Description: This file contains the serial UART control code
// Author: Andrew Cragg
// Date: March 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//============================================================================//

#include "serial.h"

//------------------------------------------------------------------------------
// Module Scope Globals
    static u_int8 current_baud = BAUD_9600;
    static char uca0_rx_buff[BUF_SIZE];
    static char uca0_tx_buff[BUF_SIZE];
    
    static int uca0_rx_buff_length = 0;
    static int uca0_tx_buff_length = 0;
    
    static int uca0_tx_buff_pos = 0;
    
    static int rx_complete_flag = FALSE;
    static int tx_ready_flag = TRUE;
//------------------------------------------------------------------------------
    

//------------------------------------------------------------------------------
// Function Name : init_serial_uart
//
// Description: This function sets up the basic serial UART system.
// Arguements: void
// Returns:    void
//
// Author: Andrew Cragg
// Date: March 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void init_serial_uart()
{  
  // Configure UART 0
  UCA0CTLW0 = 0; // Use word register
  UCA0CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
  UCA0CTLW0 |= UCSWRST; // Set Software reset enable
 
  UCA0BRW = 52; // 9,600 Baud
  UCA0MCTLW = 0x4911 ;
  UCA0CTL1 &= ~UCSWRST; // Release from reset
  UCA0IE |= UCRXIE; // Enable RX interrupt
  UCA0IE |= UCTXIE; // Enable TX interrupt

  // Configure UART 1
  UCA1CTLW0 = 0; // Use word register
  UCA1CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
  UCA1CTLW0 |= UCSWRST; // Set Software reset enable
 
  UCA1BRW = 52; // 9,600 Baud
  UCA1MCTLW = 0x4911 ;
  UCA1CTL1 &= ~UCSWRST; // Release from reset
  UCA1IE |= UCRXIE; // Enable RX interrupt
  UCA1IE |= UCTXIE; // Enable TX interrupt
}

//------------------------------------------------------------------------------
// Function Name : get_current_baud
//
// Description: This function returns the current baud rate as set in the local
//              static variable.
// Arguements: void
// Returns:    u_int8           current_baud
//
// Author: Andrew Cragg
// Date: March 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
u_int8 get_current_baud()
{
  return current_baud;
}

//------------------------------------------------------------------------------
// Function Name : set_current_baud
//
// Description: This function sets the current baud rate variable to the passed
//              value.
// Arguements: u_int8           set_baud_rate
// Returns:    void
//
// Author: Andrew Cragg
// Date: March 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void set_current_baud(u_int8 set_baud_rate)
{
  current_baud = set_baud_rate;
  
  if(current_baud == BAUD_9600)
  {
    UCA0CTLW0 |= UCSWRST; // Set Software reset enable
    UCA0BRW = 52; // 9,600 Baud
    UCA0MCTLW = 0x4911;
    UCA0CTL1 &= ~UCSWRST; // Release from reset
    UCA0IE |= UCRXIE; // Enable RX interrupt
    UCA0IE |= UCTXIE; // Enable TX interrupt
  }
  else if(current_baud == BAUD_115200)
  {
    UCA0CTLW0 |= UCSWRST; // Set Software reset enable
    UCA0BRW = 4; // 115,200 Baud
    UCA0MCTLW = 0x5551 ;
    UCA0CTL1 &= ~UCSWRST; // Release from reset
    UCA0IE |= UCRXIE; // Enable RX interrupt
    UCA0IE |= UCTXIE; // Enable TX interrupt
  }
}

//------------------------------------------------------------------------------
// Function Name : receive_char
//
// Description: This function appends the recived chars to the rx_buff
// Arguements: char           receive_char
// Returns:    void
//
// Author: Andrew Cragg
// Date: March 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void receive_char(char received_char)
{
  uca0_rx_buff[uca0_rx_buff_length++] = received_char;
  uca0_rx_buff[uca0_rx_buff_length] = NULL_TERM;
  if(uca0_rx_buff_length == BUF_SIZE - OFF_BY_ONE) uca0_rx_buff_length = 0;
  if(received_char == NULL_TERM) rx_complete_flag = TRUE;
}

//------------------------------------------------------------------------------
// Function Name : transmit_message
//
// Description: This function sets the tx buffer to a passed string
// Arguements: char           message
// Returns:    void
//
// Author: Andrew Cragg
// Date: March 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void transmit_message(char* message)
{
  int count = uca0_tx_buff_length;
  if(tx_ready_flag)
  {
    tx_ready_flag = FALSE;
    while(count < BUF_SIZE - OFF_BY_ONE) 
    {
      uca0_tx_buff[count] = message[count];
      count++;
    }
    uca0_tx_buff[BUF_SIZE - OFF_BY_ONE] = NULL_TERM;
  }
  UCA0TXBUF = uca0_tx_buff[uca0_tx_buff_length++];
}

//------------------------------------------------------------------------------
// Function Name : transmit_char
//
// Description: This function sets the uca0 tx buffer to a passed char
// Arguements: char           char_message
// Returns:    void
//
// Author: Andrew Cragg
// Date: March 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void transmit_char()
{
  int count;
  
  if(!tx_ready_flag)
  {
    UCA0TXBUF = uca0_tx_buff[uca0_tx_buff_pos];
    if(uca0_tx_buff[uca0_tx_buff_pos++] == NULL_TERM)
    {
      tx_ready_flag = TRUE;
      uca0_tx_buff_length -= uca0_tx_buff_pos; // allows transmitting multiple 
                                               // at same time
      for(count = 0; count < BUF_SIZE - OFF_BY_ONE; count++)
      {
        uca0_tx_buff[count] = uca0_tx_buff[count + uca0_tx_buff_pos]; // shifts
                                                                      // buffer
                                                                      // back
      }
      
      uca0_tx_buff_pos = 0; // resets buffer pointer for message transmitting
    }
  }
}

//------------------------------------------------------------------------------
// Function Name : receive_char
//
// Description: This function returns the pointer to the rx_buff and resets
//              the rx_complete flag
// Arguements: void
// Returns:    pointer to the uca0_rx_buff
//
// Author: Andrew Cragg
// Date: March 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
char* read_buffer(u_int8 reset)
{
  if(rx_complete_flag)
  {
    if(reset) 
    {
      rx_complete_flag = FALSE;
      uca0_rx_buff_length = 0;
    }
    return uca0_rx_buff;
  }
  
  return NULL;
}

//------------------------------------------------------------------------------
// Function Name : is_message_received
//
// Description: This function returns whether a message has been received
// Arguements: void
// Returns:    rx_complete_flag
//
// Author: Andrew Cragg
// Date: March 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
u_int8 is_message_received()
{
  return rx_complete_flag;
}

//------------------------------------------------------------------------------
// Function Name : transmit_loop
//
// Description: This function rdoes project 5
// Arguements: void
// Returns:    void
//
// Author: Andrew Cragg
// Date: March 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void transmit_loop(void)
{
  char tmp[NUM_BUF_SIZE];
  char num_string[NUM_BUF_SIZE];
  char* tmp_buf;
  int count, num;
  
  if(is_message_received())
  {
    count = 0;
    while(count < NUM_BUF_SIZE - OFF_BY_ONE) tmp[count] = tmp_buf[count];
    
    // sorry about magic numbers, messy to do conversion without them
    // string to num - max value is 65000ish 
    num = 0;
    num += (tmp[NUM_BUF_SIZE - 2] - '0') * 1; // first non null char 1's
    num += (tmp[NUM_BUF_SIZE - 3] - '0') * 10; // 10's
    num += (tmp[NUM_BUF_SIZE - 4] - '0') * 100; // 100's
    num += (tmp[NUM_BUF_SIZE - 5] - '0') * 1000; // 1000's
    num += (tmp[NUM_BUF_SIZE - 6] - '0') * 10000; // 10000's
    
    num++;
    
    // num to string
    num_string[NUM_BUF_SIZE - OFF_BY_ONE] = NULL_TERM;
    num_string[NUM_BUF_SIZE - 2] = num % 10; // 1's
    num_string[NUM_BUF_SIZE - 3] = ((num % 100) - (num % 10)) / 10; // 10's
    num_string[NUM_BUF_SIZE - 4] = ((num % 1000) - (num % 100)) / 100; // 100's
    num_string[NUM_BUF_SIZE - 5] = ((num % 10000) - (num % 1000)) / 1000; // 1000's
    num_string[NUM_BUF_SIZE - 6] = ((num) - (num % 10000)) / 10000; // 10000's
    
    display_4 = num_string;
    
    if(num <= DEMO_COUNT) transmit_message(num_string);
  }
}

//------------------------------------------------------------------------------
// Function Name : transmit_loop
//
// Description: This function clears the buffer if it has any left over
// Arguements: void
// Returns:    void
//
// Author: Andrew Cragg
// Date: March 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void start_transmit_from_buffer()
{
  tx_ready_flag = FALSE; // opposite of what you'd think but it starts the
                         // TX interrupts
}