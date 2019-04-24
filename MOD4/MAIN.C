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
pcb * pcb_add1;

int main()
{
	int i;
	//sys_stack_ptr = &sys_stack[STK_SIZE-1];
	printf("... booting MPX\n\n");

	/* Put initialization code here */
	i = initPCBs();
	if (i == 1){
		printf("(Main) Intitialized PCBs %d\n");
	} else {
		printf("(Main) Failed to initialize PCBs %d\n");
	}

	pcb_add1 = Get_PCB(PCB_list);
	Build_PCB(pcb_add1, "test1", APPLICATION_PROCESS, READY, NOT_SUSPENDED, 43, (unsigned *) _CS, (unsigned *) test1);
	Insert_PCB(&ReadyQ,pcb_add1,0);

	pcb_add = Get_PCB(PCB_list);
	Build_PCB(pcb_add, "test2", APPLICATION_PROCESS, READY, NOT_SUSPENDED, 43, (unsigned *) _CS, (unsigned *) test2);
	Insert_PCB(&ReadyQ,pcb_add,0);

	pcb_add = Get_PCB(PCB_list);
	Build_PCB(pcb_add, "test3", APPLICATION_PROCESS, READY, NOT_SUSPENDED, 43, (unsigned *) _CS, (unsigned *) test3);
	Insert_PCB(&ReadyQ,pcb_add,0);

	pcb_add = Get_PCB(PCB_list);
	Build_PCB(pcb_add, "test4", APPLICATION_PROCESS, READY, NOT_SUSPENDED, 43, (unsigned *) _CS, (unsigned *) test4);
	Insert_PCB(&ReadyQ,pcb_add,0);

	pcb_add = Get_PCB(PCB_list);
	Build_PCB(pcb_add, "test5", APPLICATION_PROCESS, READY, NOT_SUSPENDED, 43, (unsigned *) _CS, (unsigned *) test5);
	Insert_PCB(&ReadyQ,pcb_add,0);

	sys_init();
	dispatch();

	comhan();    /* Execute the command handler */

	return 0;
}
