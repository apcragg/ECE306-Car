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
    static char uca0_rx_buff[BUFF_SIZE];
    volatile  char uca0_tx_buff[BUFF_SIZE];
    
    volatile static int uca0_rx_buff_end = START_ZERO;
    volatile static int uca0_tx_buff_end = START_ZERO;
    
    volatile static int uca0_tx_buff_start= START_ZERO;
    volatile static int uca0_rx_buff_start = START_ZERO;
    
    volatile static int uca0_rx_complete_flag = FALSE;
    volatile static int uca0_tx_complete_flag = TRUE;
    
    static char uca1_rx_buff[BUFF_SIZE];
    volatile static char uca1_tx_buff[BUFF_SIZE];
    
    volatile static int uca1_rx_buff_end = START_ZERO;
    volatile static int uca1_tx_buff_end = START_ZERO;
    
    volatile static int uca1_tx_buff_start = START_ZERO;
    volatile static int uca1_rx_buff_start = START_ZERO;
    
    volatile static int uca1_rx_complete_flag = FALSE;
    volatile static int uca1_tx_complete_flag = TRUE;
    
    volatile static int uca0_num_buffered = START_ZERO;
    volatile static int uca1_num_buffered = START_ZERO;
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
  five_msec_delay(QUARTER_SECOND);
  
  PJOUT |= IOT_RESET;
  
  five_msec_delay(QUARTER_SECOND);
  
  // Configure UART 0
  UCA0CTLW0 = CLEAR_REGISTER; // Use word register
  UCA0CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
  UCA0CTLW0 |= UCSWRST; // Set Software reset enable
 
  UCA0BRW = 52; // 9,600 Baud
  UCA0MCTLW = 0x4911 ;
  UCA0CTL1 &= ~UCSWRST; // Release from rese
  UCA0IV = CLEAR_REGISTER;
  UCA0IFG &= ~UCTXIFG;
  UCA0IE |= UCRXIE; // Enable RX interrupt
  UCA0IE |= UCTXIE; // Enable TX interrupt

  // Configure UART 1
  UCA1CTLW0 = CLEAR_REGISTER; // Use word register
  UCA1CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
  UCA1CTLW0 |= UCSWRST; // Set Software reset enable
 
  UCA1BRW = 52; // 9,600 Baud
  UCA1MCTLW = 0x4911 ;
  UCA1CTL1 &= ~UCSWRST; // Release from reset
  UCA1IFG &= ~UCTXIFG;
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
void uca0_set_current_baud(u_int8 set_baud_rate)
{
  current_baud = set_baud_rate;
  
  if(current_baud == BAUD_9600)
  {
    UCA0CTLW0 |= UCSWRST; // Set Software reset enable
    UCA0BRW = BRW_9600; // 9,600 Baud
    UCA0MCTLW = MCTL_9600;
    UCA0CTL1 &= ~UCSWRST; // Release from reset
    UCA0IFG &= ~UCTXIFG;
    UCA0IE |= UCRXIE; // Enable RX interrupt
    UCA0IE |= UCTXIE; // Enable TX interrupt
  }
  else if(current_baud == BAUD_115200)
  {
    UCA0CTLW0 |= UCSWRST; // Set Software reset enable
    UCA0BRW = BRW_115200; // 115,200 Baud
    UCA0MCTLW = MCTL_115200 ;
    UCA0CTL1 &= ~UCSWRST; // Release from reset
    UCA0IFG &= ~UCTXIFG;
    UCA0IE |= UCRXIE; // Enable RX interrupt
    UCA0IE |= UCTXIE; // Enable TX interrupt
  }
}

void uca1_set_current_baud(u_int8 set_baud_rate)
{
  current_baud = set_baud_rate;
  
  if(current_baud == BAUD_9600)
  {
    UCA1CTLW0 |= UCSWRST; // Set Software reset enable
    UCA1BRW = BRW_9600; // 9,600 Baud
    UCA1MCTLW = MCTL_9600;
    UCA1CTL1 &= ~UCSWRST; // Release from reset
    UCA1IFG &= ~UCTXIFG;
    UCA1IE |= UCRXIE; // Enable RX interrupt
    UCA1IE |= UCTXIE; // Enable TX interrupt
  }
  else if(current_baud == BAUD_115200)
  {
    UCA1CTLW0 |= UCSWRST; // Set Software reset enable
    UCA1BRW = BRW_115200; // 115,200 Baud
    UCA1MCTLW = MCTL_115200 ;
    UCA1CTL1 &= ~UCSWRST; // Release from reset
    UCA1IFG &= ~UCTXIFG;
    UCA1IE |= UCRXIE; // Enable RX interrupt
    UCA1IE |= UCTXIE; // Enable TX interrupt
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
void uca0_receive_char(char received_char)
{
  if(received_char == NULL_TERM || received_char == C_RETURN)
  {
    uca0_rx_buff[uca0_rx_buff_end++] = NULL_TERM;
    uca0_rx_complete_flag = TRUE;
  }
  else
  {
    uca0_rx_buff[uca0_rx_buff_end++] = received_char;
    uca0_rx_buff[uca0_rx_buff_end] = NULL_TERM;
    uca0_rx_buff_end %= BUFF_SIZE;
  }
}

void uca1_receive_char(char received_char)
{
  if(//received_char == NULL_TERM || received_char == C_RETURN || 
     received_char == '\n')
  {
    uca1_rx_buff[uca1_rx_buff_end++] = '\n';
    uca1_rx_buff[uca1_rx_buff_end] = NULL_TERM;
    uca1_rx_complete_flag = TRUE;
  }
  else
  {
    uca1_rx_buff[uca1_rx_buff_end++] = received_char;
    uca1_rx_buff[uca1_rx_buff_end] = NULL_TERM;
    uca1_rx_buff_end %= BUFF_SIZE;
  }
}

//------------------------------------------------------------------------------
// Function Name : transmit_message
//
// Description: This function sets the tx buffer to a passed string. Worst case
//              performance of ~2k cycles to TX a full buffer.
// Arguements: char           message
// Returns:    void
//
// Author: Andrew Cragg
// Date: March 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
void uca0_transmit_message(char* message, int offset)
{
  int count = START_ZERO;
  bool end = FALSE;
  
  while(!end) 
  {
    uca0_tx_buff[(count + uca0_tx_buff_end) % BUFF_SIZE] 
      = message[(offset + count) % BUFF_SIZE];
   
    count++;
   
    if((message[(offset + count) % BUFF_SIZE] == NULL_TERM || count >= BUFF_SIZE)) 
    {
      if(count == OFF_BY_ONE) 
        count--;
      end = TRUE;
    }
  }
  uca0_tx_buff[(count++ + uca0_tx_buff_end) % BUFF_SIZE] = NULL_TERM;

  uca0_tx_buff_end = (count + uca0_tx_buff_end) % BUFF_SIZE;
  
  if(uca0_tx_complete_flag)
  {
    uca0_tx_complete_flag = FALSE;
    UCA0IFG |= UCTXIFG;
  }
  else
  {
    uca0_num_buffered++;
  }
}

void uca1_transmit_message(char* message, int offset)
{
  int count = START_ZERO;
  bool end = FALSE;
  
  while(!end) 
  { 
    uca1_tx_buff[(count + uca1_tx_buff_end) % BUFF_SIZE] 
      = message[(offset + count) % BUFF_SIZE];
   
    count++;
   
    if(message[(offset + count) % BUFF_SIZE] == C_RETURN || count >= BUFF_SIZE) 
    {
      if(count == OFF_BY_ONE) 
        count--;
      end = TRUE;
    }
  }
  uca1_tx_buff[(count++ + uca1_tx_buff_end) % BUFF_SIZE] = C_RETURN;
  
  uca1_tx_buff_end = (count + uca1_tx_buff_end) % BUFF_SIZE;
  
  if(uca1_tx_complete_flag)
  {
    uca1_tx_complete_flag = FALSE;
    UCA1IFG |= UCTXIFG;
  }
  else
  {
    uca1_num_buffered++;
  }
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
void uca0_transmit_char()
{ 
  if(!uca0_tx_complete_flag)
  {
    if( uca0_tx_buff[uca0_tx_buff_start] == NULL_TERM)
    {
      if(uca0_num_buffered) 
        uca0_num_buffered--;
      else
        uca0_tx_complete_flag = TRUE;          
    }
    UCA0TXBUF = uca0_tx_buff[uca0_tx_buff_start++];
    uca0_tx_buff_start %= BUFF_SIZE;
  }
}

void uca1_transmit_char()
{ 
  if(!uca1_tx_complete_flag)
  {
    if(uca1_tx_buff[uca1_tx_buff_start] == C_RETURN)
    {
      UCA1TXBUF = uca1_tx_buff[uca1_tx_buff_start];
      if(uca1_num_buffered) 
        uca1_num_buffered--;
      else
        uca1_tx_complete_flag = TRUE;       
    }
      UCA1TXBUF = uca1_tx_buff[uca1_tx_buff_start++];
    uca1_tx_buff_start %= BUFF_SIZE;
  }
}

//------------------------------------------------------------------------------
// Function Name : receive_char
//
// Description: This function returns the pointer to the rx_buff and resets
//              the rx_complete flag. FIFO buffer.
// Arguements: void
// Returns:    pointer to the uca0_rx_buff
//
// Author: Andrew Cragg
// Date: March 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//------------------------------------------------------------------------------
BufferString uca0_read_buffer(u_int8 reset)
{
  // Volatile access things
  BufferString buffer;
  int rx_buffer_start = uca0_rx_buff_start;
  int rx_buffer_end = uca0_rx_buff_end;
  
  buffer.head = uca0_rx_buff;
  buffer.offset = rx_buffer_start;
  if(reset) 
  {     
    uca0_rx_complete_flag = FALSE;
    uca0_rx_buff_start = rx_buffer_end;
  }
  return buffer;
}

BufferString uca1_read_buffer(u_int8 reset)
{
   // Volatile access things
  BufferString buffer;
  int rx_buffer_start = uca1_rx_buff_start;
  int rx_buffer_end = uca1_rx_buff_end;
  
  buffer.head = uca1_rx_buff;
  buffer.offset = rx_buffer_start;
  if(reset) 
  {     
    uca1_rx_complete_flag = FALSE;
    uca1_rx_buff_start = rx_buffer_end;
  }  
  return buffer;
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
u_int8 uca0_is_message_received()
{
  return uca0_rx_complete_flag;
}

u_int8 uca1_is_message_received()
{
  return uca1_rx_complete_flag;
}