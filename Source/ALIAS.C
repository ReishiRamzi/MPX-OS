/*  file:  alias.c
 *
 * This file allows the user to change the alias of a specified command
 * in the command handler
 */

#include "mpx.h"


// takes a pointer to the alias array, the arguments list, and the index of the command
void alias(char *aliasArray[], char *arguments[], int index)
{
    // if either argument is null, invalid assignment
    if (arguments[1] == '\0' || arguments[2] == '\0' || index == -1)
    {
	printf("Invalid alias assignment.%d\n", 0);
	return;
    }
    // the alias is the third argument, i.e. alias copy cp sets cp as an alias for copy`
    aliasArray[index] = arguments[2];
}
