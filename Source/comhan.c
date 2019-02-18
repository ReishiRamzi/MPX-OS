/* test
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

        // PLACEHOLDER/CONCEPT FOR FUTURE IMPLEMENTATION
        // this should get the length of an array. size of determines
        // the amount of bytes in whatever is passed into it.
        // This should get the # of bytes in the array cmds, then
        // divide them by the size of a pointer to a char.
        // In theory, anyway.
        int cmdArrLen = sizeof(cmds) / sizeof(*char);
        int cmdMatch = -1;
        int cmdMatch2 = -1;
        // strcmp compares strings to see if they have the same value.
        // if two strings return 0, they are the same.
        if (args[0] != NULL){
            for (int i = 0; i < cmdArrLen; i++){
                if (strcmp(args[0], cmds[i]) == 0){
                    cmdMatch = i;
                }
            }
        }
        if (args[1] != NULL){
            for (int i = 0; i < cmdArrLen; i++){
                if (strcmp(args[1], cmds[i]) == 0){
                    cmdMatch2 = i;
                }
            }
        }
        // switch command changes depending on the command match
        switch (cmdMatch + 1){
            case 1:
                char helpReturn;
                if (cmdMatch2 > -1 && cmdMatch2 < cmdArrLen){
                    helpReturn = help(cmdMatch2,cmdArrLen);
                } else {
                    helpReturn = help(-1, cmdArrLen);
                }
                printf(helpReturn);
                break;
            case 2:
                //Version
                break;
            case 3:
                //Date
                break;
            case 4:
                //Quit
                break;
            case 5:
                //Directory
                break;
            case 6:
                //Prompt
                break;
            case 7:
                //Alias
                break;
            default:
                printf("Invalid command.");
                break;
        }
        /*
        // Every example of switch statements has a return 0 at the end
        // but i dont know why or if it's necessary.
        return 0;
        */

        // END PLACEHOLDER

    } while(1);
}

int set_args(char *buffer, char *arcs[])
{
    static char separators[5] = " =";

    static int i;

    i = 0;

    strlwr(buffer);

    args[i] = strtok(buffer, separators);

    // FINDS FIRST CHAR THEN FINDS SEPERATOR IN STRING
    // AND REPLACES IT WITH NULL
    while(args[i] != NULL) {
        args[++i] = strtok(NULL, separators);
    }

    return i;
}
