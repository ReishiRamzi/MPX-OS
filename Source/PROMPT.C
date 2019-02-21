/*  file:  prompt.c
 *
 * This file allows the user to change the prompt
 * of the operating system
 */

#include "mpx.h"

// checks the prompt and returns the new prompt if it is in The
// correct format
char* changePrompt(char *currPrompt, char *argument[]){
	char arg;
	strcpy(arg,argument[1]);
	//printf("CPROMPT: %s, NPROMPT: %s\n",currPrompt, arg);
	if (argument[1][10] == '\0'){
		//printf("working\n");
		return arg;
	}
	printf("** Invalid argument - %s\n", arg);
	return currPrompt;
}
