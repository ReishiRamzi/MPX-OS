/*
    file:   help.c

    This file contains the function that returns a synopsis of the various commands in the command
    handler.
*/
#include <stdio.h>
#include "mpx.h"

char *helpList[] =
{
    "Help List\n",
    "----------------------------------------------------\n",
    "help [command]       - Print command help\n",
    "version              - MPX version number\n",
    "date [mm/dd/yy]      - View/change system date\n",
	"quit                 - Terminates MPX\n",
    "directory            - List .mpx files\n",
    "prompt=string        - Change MPX promt\n",
	"alias                - Assign string to command\n",
    "show command         - Prints list of PCBs\n",
    "allocate data-x6     - Makes PCB with requested data\n",
    "free name            - Frees PCB with matching name\n",
    "load name [ppp]      - Makes PCB of name & priority\n",
    "resume name          - Makes PCB not suspended\n",
    "run name [ppp]       - Makes PCB and sets to ready\n",
    "suspend name         - Suspends PCB called name\n",
    "terminate name       - Terminates PCB called name\n",
    "setpriority name ppp - Sets PCB's priority\n",
	"dispatch             - Dispatches a process\n",
	"clock command        - Stops, Starts or Sets Clock\n"
};

// takes a command to print help information about -
// returns a string, if no command given returns all
void help(char* args, int argc, int cmdMatch){
	int i;
	// if number of arguments is greater than two, invalid
	if (argc > 2) {
        printf("Too many arguments. Commands used: %d. Please use only one command. \n", argc);
    } else if (argc == 1) {
        for (i = 0; i < NUM_CMDS+2; i++) {
            printf("%s", helpList[i]);
        }
    } else {
        printf("%s",helpList[cmdMatch+2]);
    }
}
