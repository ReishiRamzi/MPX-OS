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

char prompt[MAXSIZE] = "mpx>";

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
	"show",
	"allocate",
	"free",
	"\0"
};

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
	// flag for running - initialize to on = 1
	int running = 1;

	// an index for the matched command
	int cmdMatch;
	int numDirects;
	int i;
	int returnInt;

	do {
		args[0] = NULL;
		args[1] = NULL;
		args[2] = NULL;
		printf("%s ",prompt);              /* Print a prompt.         */
		length = BUF_SIZE;                 /* Reset length of buffer. */
		sys_reqc(CON,READ,buffer,&length);  /* Request CON input       */
		// get number of arguments and set arguments
		argc = set_args(buffer, args);
		// match a command in the argument set
		cmdMatch = matchCommand(args, 0);
		// echo arguments
		//printf("ARGS0 %s, ARGS1 %s, ARGS2 %s\n",args[0], args[1], args[2]);

		// Switch statement for the different commands
		switch(cmdMatch){
			case 0:
				//help
				help(args, argc, matchCommand(args, 1));
				// call the help function and print its return
				// printf("%s", help(args, argc, cmdMatch));
				break;
			case 1:
				//version
				printf("Current Version: %s\n",version());
				break;
			case 2:
				//date
				if (args[1] != NULL){
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
				numDirects = directory(direct, MAXSIZE);
				//printf("DIRECTORY COMMAND\n");
				printf("Number of files: %d\n", numDirects);
				break;
			case 5:
				//prompt
				strcpy(prompt,changePrompt(prompt, args));
				//printf("AFTER: %s\n",prompt);
				//printf("PROMPT COMMAND\n");
				break;
			case 6:
				//alias
				alias(als, args, matchCommand(args,1));
				break;
			case 7:
				// show
				show(args[1]);
				break;
			case 8:
				// allocate
				for(i = 0; i < argc; i++){
					printf("args %d: %s\n", i, args[i]);
				}
				returnInt = Allocate(args[1],args[2],args[3],args[4],args[5],args[6]);
				printf("%d",returnInt);
				break;
			case 9:
				// free
				returnInt = Free(args[1]);
				printf("%d",returnInt);
				break;
			default:
			// such as -1
				printf("Invalid Command.\n");
				break;
		}
	} while (running == 1);
};

// returns the index of the command that matches command line arguments
int matchCommand(char *array[], int index)
{
	int thisMatch = -1;
	int i;

	//printf("%s",args[0]);            // for debugging
	// number of commands already stored in argc (arguments count)
	// length already stored in length - set in sys_reqc.c from sys_req()
	//cmdArrLen = sizeof(cmds) / sizeof(cmds[0]);
	//cmdMatch2 = -1;
	// if there are arguments, i.e. the first argument is not null
	if (array[0] != '\0'){
		// and check our first argument against each possible command and alias
		// TODO: 7 commands currently, should convert to variable
		for (i = 0; i < NUM_CMDS; i++)
		{
			// if there's a match in cmds or als
			if ((strcmp(array[index], cmds[i]) == 0) || (strcmp(array[index], als[i]) == 0))
			{
				// set the match flag to the index of the command
				thisMatch = i;
				return thisMatch;
			}
		}
	}
	return thisMatch;

}
// takes a pointer to the desired buffer and a pointer to the array of arguments
// fills arguments array with tokenized buffer input and returns number of arguments
int set_args(char *buffer, char *args[]){
	static char seperators[5] = " =,";
	static int i;

	i = 0;

	strlwr(buffer);

	args[i] = strtok(buffer, seperators);

	while (args[i] != NULL) {
		args[++i] = strtok(NULL, seperators);
	}

	return i;
};
