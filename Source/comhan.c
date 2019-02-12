/*
*   comhan.c
*   02/06/2019
*   COMHAN (Command Handler) is the command interface for MPX
*   Its role is to:
*   1. read a command entered via the system console keyboard
*   2. analyze the command 
*   3. execute the command
*
*/

#include "comhan.h"

// size of the command line buffer
#define BUF_SIZE 80

// length of the command line
int length;

// stores the command line argument
char buffer[BUF_SIZE];

// array of pointers to the command line arguments
char *args[10];

// command line argument counter
int argc;

// our default prompt
char prompt[20] = "mpx>";

// default version information
const char version[] = "MPX OS - Version 1.0\n";

// array of pointers to strings for our commands
char *cmds[] = 
{
    "help",
    "version",
    "date",
    "quit",
    "directory",
    "prompt",
    "alias",
    NULL    
};

// array of pointers to aliases for our string commands
char *als[] = 
{
    "   ",
    "   ",
    "   ",
    "   ",
    "   ",
    "   ",
    "   ",
    NULL
};

/*
    COMHAN - this is the command handler for the MPX OS
*/

void comhan()
{
    do
    {
        printf("\n%s ", prompt);
        length = BUF_SIZE;
        sys_req(CON, READ, buffer, &length);

        argc = set_args(buffer, args);
    } while(1);    
}

int set_args(char *buffer, char *arcs[])
{
    static char separators[5] = " =";

    static int i;

    i = 0;

    strlwr(buffer);

    args[i] = strtok(buffer, separators);
    
    while(args[i] != NULL) {
        args[++i] = strtok(NULL, separators);  
    }
    
    return i;
}