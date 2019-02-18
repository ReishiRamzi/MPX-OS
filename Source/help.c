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

char help(int helpCmd, int numCmds){
    char helpOut;
    if (helpCmd > -1){
        helpOut = helpList[helpCmd + 2];
    } else {
        strcpy(helpOut, helpList[0]);
        for (int i = 1; i < (numCmds + 2); i++){
            // concatenates each line of the list to helpOut
            strcat(helpOut, helpList[i]);
        }
    }

    return helpOut;
}
