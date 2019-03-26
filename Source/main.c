/*  file:  main.c
 *
 *  This file contains the function main
 *  for the MPX Operating System - this is where
 *  the program's execution begins
 */
#include <stdio.h>
#include <stdio.h>
#include "mpx.h"

pcb * pcb_add;

int main()
{
	int i;
	//sys_stack_ptr = &sys_stack[STK_SIZE-1];
	printf("... booting MPX\n\n");

	/* Put initialization code here */
	i = initPCBs();
	if (i == 1){
		printf("intitialized PCBs %d\n", i);
	} else {
		printf("whoops %d\n", i);
	}

	pcb_add = Get_PCB(PCB_list);
	Build_PCB(pcb_add, "test1", APPLICATION_PROCESS, READY, NOT_SUSPENDED, 43, (unsigned *) _CS, (unsigned *) test1);
	Insert_PCB(&ReadyQ,pcb_add,0);
	//temp->stack[STACK_PSW] = INT_ENABLE;
	//temp->stack[STACK_CS] = _CS;
	//temp->stack[STACK_IP] = &test1;
	comhan();    /* Execute the command handler */

	return 0;
}
