/*  file:  alias.c
 *
 * This file allows the user to change the alias of a specified command
 * in the command handler
 */

#include "mpx.h"


// takes a pointer to the alias array, the arguments list, and the index of the command
void alias (char *aliasArr[], char* args[], int index){
    // if either argument is null, invalid assignment
    if (args[1] == '\0' || args[2] == '\0')
    {
	    printf("Invalid alias assignment.\n");
        return;
    }
    // the alias is the third argument, i.e. alias copy cp sets cp as an alias for copy`
    char* newAlias = args[2];
    aliasArr[index] = newAlias;
    printf("IN ALIAS.C: %s", newAlias);
}
