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
static int NUM_CMDS;
// Array of pointers to strings for our commands
char *cmds[] =
{
	"help",
	"version",
	"date",
	"quit",
	"directory",
	"prompt",
	"alias",
	"\0"
};
// set number of commands...
// TODO: make a function
NUM_CMDS = 7;
// Array of pointers to aliases for our commands
char *als[] =
{
	"   ",
	"   ",
	"   ",
	"   ",
	"   ",
	"   ",
	"   ",
	"\0"
};

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
	//int cmdArrLen;
	int cmdMatch;
	//int cmdMatch2;
	int i;
	char returnPrint;
	do {
		args[0] = '\0';
		args[1] = '\0';
		args[2] = '\0';
		printf("%s ",prompt);              /* Print a prompt.         */
		length = BUF_SIZE;                 /* Reset length of buffer. */
		sys_req(CON,READ,buffer,&length);  /* Request CON input       */
		argc = set_args(buffer, args);
		//printf("%s",args[0]);            // for debugging
		// number of commands already stored in argc (arguments count)
		// length already stored in length - set in sys_reqc.c from sys_req()
		//cmdArrLen = sizeof(cmds) / sizeof(cmds[0]);
		cmdMatch = -1;
		//cmdMatch2 = -1;
		// if there are arguments, i.e. the first argument is not null
		if (args[0] != '\0'){
			// and check our first argument against each possible command and alias
			// TODO: 7 commands currently, should convert to variable
			for (i = 0; i < NUM_CMDS; i++)
			{
				// if there's a match in cmds or als
				if ((strcmp(args[0], cmds[i]) == 0) || (strcmp(args[0], als[i]) == 0))
				{
					//set the match flag to the index of the command
					cmdMatch = i;
				}
			}
		}

		printf("ARGS0 %s, ARGS1 %s, ARGS2 %s\n",args[0], args[1], args[2]);

		// Switch statement for the different commands
		switch(cmdMatch){
			case 0:
				//help
				// call the help function and print its return
				printf("%s", help(args, argc, cmdMatch));			
				break;
			case 1:
				//version
				printf("Current Version: %s\n",version());
				break;
			case 2:
				//date
				if (args[1] != '\0'){
				    upDate(args[1]);
				} else {
				    printf("Current Date: %s\n", getDate());
				}
				break;
			case 3:
				//quit
				printf("Shutting down MPX\n");
				running = quit();
				break;
			case 4:
				//directory
				printf("DIRECTORY COMMAND\n");
				break;
			case 5:
				//prompt
				printf("PROMPT COMMAND\n");
				break;
			case 6:
				//alias
				alias(*als, args, cmdMatch);
				// confirm it worked
				printf("CMD: %s, NEW ALIAS: %s\n",cmds[cmdMatch], als[cmdMatch]);
				break;
			default:
				printf("Invalid Command.\n");
				break;
		}
	} while (running == 1);
};
int matchCommand()
{

}
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
