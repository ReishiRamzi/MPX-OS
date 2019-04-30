/*  file:  ManageCo.c
 *
 * This file contains the management commands to interact with PCBs.
 *
 */
 #include <stdio.h>
 #include "mpx.h"

 // sp_save saves the pointer value before the call minus the number of elements
 // on the stack after dispatch recieves control.
 int *sp_save;

 // Assigns the appropriate information to a PCB in the SUSPENDED state
 // THIS REQUIRES THE load.c SUPPORT PROCEDURE FOR THIS MODULE
 // load( (ADDRESS FROM ALLOCMEM), name);
 // alloc mem num paragraphs = (num bytes of file/ 16) + 1
 void Load(char *name, char *priority){
	int intPriority;
	pcb * pcb_add;
	int size;
	unsigned * segment;
	size = (GetSize(name)/16)+1;
	allocmem(size,&segment);
	load(segment,name);
	intPriority = atoi(priority);
	pcb_add = Get_PCB(PCB_list);
	if (pcb_add != NULL){
		if (priority != NULL){
			// THIS REQUIRES THE load.c SUPPORT PROCEDURE FOR THIS MODULE
			Build_PCB(pcb_add, name, APPLICATION_PROCESS, READY, SUSPENDED, intPriority, segment, 0);
			Insert_PCB(&ReadyQ,pcb_add,0);
		} else {
			// THIS REQUIRES THE load.c SUPPORT PROCEDURE FOR THIS MODULE
			Build_PCB(pcb_add, name, APPLICATION_PROCESS, READY, SUSPENDED, DEFAULT_PRIORITY, segment, 0);
			Insert_PCB(&ReadyQ,pcb_add,0);
		}
	} else {
		printf("(Load) No free PCBs.\n");
	}
 }

 // Checks for a PCB by name and sets it to NOT_SUSPENDED
 void Resume(char *name){
	 pcb * pcb_add;
	 pcb_add = Search_PCB(PCB_list, name);
	 if (pcb_add != NULL){
		 pcb_add->suspend = NOT_SUSPENDED;
	 } else {
		 printf("(Resume) %s was not found.\n", name);
	 }
 }

 // Assigns the requested information to a PCB then sets it to NOT_SUSPENDED
 // This can be rewritten to essentially just be Load() but setting the suspend to NOT_SUSPENDED instead.
 void Run(char *name, char *priority){
	 Load(name,priority);
	 Resume(name);
 }

 // Checks for a PCB by name and sets it to SUSPENDED as long as it isn't a SYSTEM_PROCESS
 void Suspend(char *name){
	 pcb * pcb_add;
	 pcb_add = Search_PCB(PCB_list, name);
	 if (pcb_add != NULL){
		 if (pcb_add->type != SYSTEM_PROCESS){
			 pcb_add->suspend = SUSPENDED;
		 } else {
			 printf("(Suspend) %s cannot be suspended because it is a system process.\n", name);
		 }
	 } else {
		 printf("(Suspend) %s was not found.\n", name);
	 }
 }
 // Frees the requested PCB as long as it exists.
 void Terminate(char *name){
	 pcb * pcb_add;
	 pcb_add = Search_PCB(PCB_list, name);
	 if (pcb_add != NULL){
		 if (pcb_add->type != SYSTEM_PROCESS){
			 Free_PCB(PCB_list, pcb_add);
		 } else {
			 printf("(Terminate) %s cannot be terminated because it is a system process.\n", name);
		 }
	 } else {
		 printf("(Terminate) %s was not found.\n", name);
	 }
 }

 // Sets a PCB's priority as long as it isn't a SYSTEM_PROCESS and the requested
 // priority is valid.
 // TAKE PCB OUT OF Q FIRST, THEN CHANGE PRIORITY, THEN PUT BACK IN
 void SetPriority(char *name, char *priority){
	 int intPriority;
	 pcb * pcb_add;
	 intPriority = atoi(priority);
	 pcb_add = Search_PCB(PCB_list, name);
	 if (pcb_add != NULL){
		 if (pcb_add->type != SYSTEM_PROCESS){
			 if (intPriority > -127 && intPriority < 127){
				 Remove_PCB(&ReadyQ, pcb_add);
				 pcb_add->priority = intPriority;
				 Insert_PCB(&ReadyQ, pcb_add, 0);
			 }
		 } else {
			 printf("(SetPriority) %s cannot have it's priority changed because it is a system process.\n", name);
		 }
	 } else {
		 printf("(SetPriority) %s was not found.\n", name);
	 }
 }

 // Dispatches one at a time, then returns control to COMHAN
 void Dispatch_CMD(){
	 static pcb dummy_pcb;

	 printf("(Dispatch_CMD) Entering Dispatch_CMD...\n");

	 /* Set cop to point to the dummy PCB that points to the first PCB in
		ReadyQ to force one-pass round robin dispatcher to start at the
		front of the ready queue                                         */

	 cop = &dummy_pcb;
	 cop->prev = ReadyQ;

	 printf("(Dispatch_CMD) Assigned cop to dummy_pcb and cop->prev to ReadyQ\n");

	 /* Save COMHAN's stack pointer */

	 sp_save = _SP - DISP_OFFSET;

	 printf("(Dispatch_CMD) Saving _SP - DISP_OFFSET to sp_save\n");

	 printf("(Dispatch_CMD) Calling dispatch()...\n");
	 dispatch();
 }
