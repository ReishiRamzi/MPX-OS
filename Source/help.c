/*
    file:   help.c

    This file contains the function that returns a synopsis of the various commands in the command
    handler.
*/

#include "mpx.h"

char *helpList[] =
{
    "Help List\n",
    "---------------------------------------------\n",
    "help [command]     - Print command help\n",
    "version            - MPX version number\n",
    "date [mm/dd/yy]    - View/change system date\n",
    "stop               - Terminates MPX\n",
    "directory          - List .mpx files\n",
    "prompt=string      - Change MPX promt\n",
    "alias              - Assign string to command\n"
};

// takes a command to print help information about - 
// returns a string, if no command given returns all
char* help(char* args, int argc, int cmdMatch){
    char* helpOut;

    // if number of arguments is greater than two, invalid
    if (argc > 2)
    {
        printf("Too many arguments. Commands used: %d. Please use only one command. \n", argc);
    }

    // if invalid help request print to console
    else if (cmdMatch == -1)
    {
        printf("Invalid help command. Please try again. \n");
    }

    // if no argument print all help
    else if (args[1] == '\0')
    {
        helpOut = helpList;
    }
    // otherwise, return the string of the requested help function
    else
    {
        strcpy(helpOut, helpList[cmdMatch]);
    }
    // return our string
    return helpOut;
}
