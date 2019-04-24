/*  file:  ManageComs.c
 *
 * This file contains the management commands to interact with PCBs.
 *
 */
 #include <stdio.h>
 #include "mpx.h"

 int Load(char *name, int priority){
	pcb * pcb_add;
	pcb_add = Get_PCB(PCB_list);
	if (priority != NULL){
		Build_PCB(pcb_add, name, APPLICATION_PROCESS, READY, SUSPENDED, priority, (unsigned *) _CS, (unsigned *) test5);
		Insert_PCB(&ReadyQ,pcb_add,0);
	} else {
		Build_PCB(pcb_add, name, APPLICATION_PROCESS, READY, SUSPENDED, 77, (unsigned *) _CS, (unsigned *) test5);
		Insert_PCB(&ReadyQ,pcb_add,0);
	}
 }