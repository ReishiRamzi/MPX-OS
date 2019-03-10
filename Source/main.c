/*  file:  main.c
 *
 *  This file contains the function main
 *  for the MPX Operating System - this is where
 *  the program's execution begins
 */

#include <stdio.h>
#include "mpx.h"


int main()
{
	int i;
	printf("... booting MPX\n\n");

	/* Put initialization code here */
	i = initPCBs();
	if (i == 1){
		printf("intitialized PCBs %d\n", i);
	} else {
		printf("whoops %d\n", i);
	}

	comhan();    /* Execute the command handler */

	return 0;
}
