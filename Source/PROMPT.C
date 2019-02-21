
#include "mpx.h"

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
