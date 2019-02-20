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

char *args[10];          // Array of pointers to cmd line args
int argc;                // Stores count of args

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
	int running = 1;
	do {
	printf("%s ",prompt);              /* Print a prompt.         */
	length = BUF_SIZE;                 /* Reset length of buffer. */
	sys_req(CON,READ,buffer,&length);  /* Request CON input       */
	argc = set_args(buffer, args);
	printf("%s",args[0]);
	if (strcmp(args[0], "quit") == 0){
		running = quit();
	}
	// for debugging
	// running = 0;
	} while (running == 1);
};

int set_args(char *buffer, char *args[]){
	static char seperators[5] = " =";
	static int i;

	i = 0;

	strlwr(buffer);

	args[i] = strtok(buffer, seperators);

	while (args[i] != '\0') {
		args[++i] = strtok('\0', seperators);
	}

	return i;
};
