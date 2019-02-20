/*
 *   file:  comhan.c
 *
 *   This file is the command handler for the
 *   MPX operating system.
 */

#include <stdio.h>
#include <string.h>
#include "mpx.h"

#define BUF_SIZE 80      /* Size of the command line buffer. */

int  length;             /* Length of the command line.      */
char buffer[BUF_SIZE];   /* Stores the command line.         */

char prompt[20] = "mpx>";

/*
 *   comhan()    This is the command handler for the MPX OS.
 *               It repeatedly prints a prompt, makes a system
 *               request to read from the console, and then
 *               carries out the command.
 *
 *   Parameters: None.
 *   Return value: None.
 */

void comhan()
{
    do {
		  printf("%s ",prompt);              /* Print a prompt.         */
		  length = BUF_SIZE;                 /* Reset length of buffer. */
		  sys_req(CON,READ,buffer,&length);  /* Request CON input       */

    } while (1);
}
