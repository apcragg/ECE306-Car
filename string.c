//============================================================================//
// File Name : string.c
//
// Description: This file contains the IOT wifi module serial command code.
// Author: Andrew Cragg
// Date: April 2016
// Compiler: Built with IAR Embedded Workbench Version: V4.10A/W32 (6.40.1)
//============================================================================//

#include "string.h"

bool compare(char* a, char* b)
{
  int i = START_VAL;
  while(a[i] == b[i])
  {
    if(a[i] == NULL_TERM && b[i] == NULL_TERM)
      return TRUE;
    i++;
  }
  
  return FALSE;
}