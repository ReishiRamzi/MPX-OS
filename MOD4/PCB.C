/*
 *    file:  pcb.c
 *
 *    This file contains the functions related to process control
 *    blocks.
 */
#include <stdio.h>
#include "mpx.h"

pcb * PCB_list; /* Pointer to first PCB */
pcb * ReadyQ;   /* Pointer to priority queue of PCBs */
pcb * IO_InitQ; /* Pointer to FIFO queue of PCBS */

pcb pcb1, pcb2, pcb3, pcb4, pcb5, pcb6, pcb7, pcb8, pcb9, pcb10;
pcb pcb11, pcb12, pcb13, pcb14, pcb15, pcb16, pcb17, pcb18, pcb19, pcb20;

int numPCBs = 20;
/*
	Set uppcbs and test procedures
	assigns variables for PCB
*/
int Allocate(char *name, char *type, char *state, char *suspend, char *priority, char *prog)
{
	int intType;
	int intState;
	int intSuspend;
	int intPriority;
	int pcbStatus;
	// get the next free pcb
	pcb *nextPCB = Get_PCB(PCB_list);

	// CHECK PROCESS TYPE
	if (strcmp(type, "a") == 0){
		intType = APPLICATION_PROCESS;
	} else if (strcmp(type, "s") == 0){
		intType = SYSTEM_PROCESS;
	} else {
		printf("failed type: %d\n", intType);
		return 0;
	}
	printf("success type\n");
	//CHECK STATE
	if (strcmp(state, "r") == 0){
		intState = READY;
	} else if (strcmp(state, "o") == 0){
		intState = RUNNING;
	} else if (strcmp(state, "b") == 0){
		intState = BLOCKED;
	} else {
		printf("failed state: %d\n", intState);
		return 0;
	}
	printf("success state\n");
	// CHECK SUSPEND
	if (strcmp(suspend, "n") == 0){
		intSuspend = NOT_SUSPENDED;
	} else if (strcmp(suspend, "y") == 0){
		intSuspend = SUSPENDED;
	} else {
		printf("failed suspend: %d\n", intSuspend);
		return 0;
	}
	printf("success suspend\n");
	// CONVERT CHAR TO INT
	intPriority = atoi(priority);

	//CHECK PRIORITY VALIDITY
	if (intPriority < -128 || intPriority > 127){
		printf("failed priority: %d\n", intPriority);
		return 0;
	}
	printf("success priority\n");
	printf("PCB ADDR: %d\n", nextPCB);
	pcbStatus = Build_PCB(nextPCB, name, intType, intState, intSuspend, intPriority, (unsigned *) _CS, (unsigned *) prog);
	return pcbStatus;
}
/*
	frees pcb
*/
int Free(char *name)
{
	pcb *pcbToFree = Search_PCB(PCB_list, name);
	printf("Searching for PCB called: %s\n",name);
	if (pcbToFree != NULL){
		printf("Name of PCB: %s",pcbToFree->procname);
		strcpy(pcbToFree->procname, NULL);
		pcbToFree->type = NULL;
		pcbToFree->priority = NULL;
		pcbToFree->state = NULL;
		pcbToFree->suspend = NULL;
	} else {
		return 0;
	}
	return 1;
}
/*
	Returns the address of a pcb with the name of pcbname[9].
	If the address isnt found (name doesnt exist), addr returns null (\0)
*/
pcb* Search_PCB(pcb *pcbPtr, char *pcbname[9]) {
	pcb *addr = NULL;
	pcb *temp = pcbPtr;
	while (temp != NULL) {
		if (strcmp(temp->procname, pcbname) == 0) {
			addr = temp;
			break;
		}
		temp = temp->chain;
	}
	return addr;
}

/*
	Returns the address of the next free pcb in the chain.
	If the address isnt found (no free pcbs), addr returns null (\0)
*/
pcb* Get_PCB(pcb *pcbPtr) {
	pcb *addr = NULL;
	pcb *temp = pcbPtr;
	while (temp != NULL) {
		if (temp->type == FREE) {
			addr = temp;
			break;
		}
		temp = temp->chain;
	}
	return addr;
}

/*
	returnInt can be 1, -1, or -2
	 1: PCB Freed
	-1: Invalid PCB address in addr
	-2: PCB is already free
*/
int Free_PCB(pcb *pcbListPtr, pcb *addr) {
	int returnInt = -1;
	pcb *temp = pcbListPtr;
	while (temp != NULL) {
		// look for the address that matches our search
		if (strcmp(temp->loadaddr, addr) == 0) {
			// already free
			if (temp->type == FREE) {
				returnInt = -2;
				break;
			} else {
				temp->type = FREE;
				// free the pcb
				returnInt = 1;
				break;
			}
		}
		// next in the chain
		temp = temp->chain;
	}
	return returnInt;
}

/*
	Checks that all parameters are valid and then applies them to PCBS
	Return values:
	 1: PCB Completed
	-1: Invalid PCB address in addr
	-2: Invalid type
	-3: Invalid state
	-4: Invalid suspend
	-5: Invalid priority
*/
int Build_PCB(pcb *addr, char *name, int type, int state, int suspend, int priority, unsigned * cs, unsigned * prog) {
	int returnInt = 0;
	int addrCheck = 0;
	int count = 0;
	//printf("(Build_PCB) Entering Build_PCB\n");
	//printf("(Build_PCB) Beginning Checks\n");
	if (suspend == 0 || suspend == 1) {
		//printf("(Build_PCB) Suspend checked\n");
		if (state > -1 && state < 3) {
			//printf("(Build_PCB) State checked\n");
			if (type > -1 && type < 3) { // if all parameters are valid,
				//printf("(Build_PCB) Type checked\n");
				if (priority >= -128 && priority <= 127){
					//printf("(Build_PCB) Priority checked\n");
					addr->suspend = suspend; // theyre applied to the PCB
					//printf("(Build_PCB) Suspend changed to %d\n", addr->suspend);
					addr->state = state;
					//printf("(Build_PCB) State changed to %d\n", addr->state);
					addr->type = type;
					//printf("(Build_PCB) Type changed to %d\n", addr->type);
					addr->priority = priority;
					//printf("(Build_PCB) Priority changed to %d\n", addr->priority);
					strcpy(addr->procname, name);
					//printf("(Build_PCB) Name changed to %s\n", addr->procname);
					addr->stack[STACK_PSW] = INT_ENABLE;
					addr->stack[STACK_CS] = cs;
					addr->stack[STACK_IP] = prog;
					addr->stack[STACK_DS] = _DS;
					addr->stack_ptr = &(addr->stack[INIT_STACK]);
					returnInt = 1;
				} else { // invalid priority
					returnInt = -5;
					//printf("(Build_PCB) Invalid Priority\n");
				}
			} else { // type is invalid
				returnInt = -2;
				//printf("(Build_PCB) Invalid Type\n");
			}
		} else { // state is invalid
			returnInt = -3;
			//printf("(Build_PCB) Invalid State\n");
		}
	} else { // suspend is invalid
		returnInt = -4;
		//printf("(Build_PCB) Invalid Suspend\n");
	}
	//printf("(Build_PCB) Finished checks\n");
	return returnInt;
}

/*
	Inserts PCB into a queue.
	Values returned:
	 1: PCB Inserted
	-1: Incorrect method
	-2: Incorrect addr
*/
int Insert_PCB(pcb **PCB_Q, pcb *addr, int method) {
	int returnInt;
	int count;
	//printf("(Insert_PCB) Entering Insert_PCB...\n");
	count = 0;
	if (addr != NULL) {
		if (method == 0) { // Insert into Priority Queue
			//printf("(Insert_PCB) Insert Method 0: Priority Queue\n");
			if (*PCB_Q == NULL) {
				//printf("(Insert_PCB) Queue passed is empty\n");
				//printf("(Insert_PCB) Adding PCB to front of Priority Queue\n");
				*PCB_Q = addr;
				(*PCB_Q)->next = NULL;
				(*PCB_Q)->prev = NULL;
				returnInt = 1; // PCB Inserted
			} else {
				//printf("(Insert_PCB) Queue passed is not empty\n");
				//printf("(Insert_PCB) Finding position in Priority Queue\n");
				while ((*PCB_Q)->prev != NULL && (*PCB_Q)->priority >= addr->priority) {
					*PCB_Q = (*PCB_Q)->prev;
					//printf("(Insert_PCB) Curr Priority %d > Address Priority %d\n",(*PCB_Q)->priority,addr->priority);
				}
				//printf("(Insert_PCB) Found position in Priority Queue\n");
				if ((*PCB_Q)->priority >= addr->priority && (*PCB_Q)->next != NULL){ // if found position is not front of queue
					(*PCB_Q)->prev->next = addr;
					addr->prev = (*PCB_Q)->prev;
					addr->next = *PCB_Q;
					(*PCB_Q)->prev = addr;

					printf("(Insert_PCB) Assigned higher position in Priority Queue.\n");
				} else if ((*PCB_Q)->priority < addr->priority && (*PCB_Q)->next != NULL){ // if found position is not front of queue
					(*PCB_Q)->next->prev = addr;
					addr->next = (*PCB_Q)->next;
					addr->prev = *PCB_Q;
					(*PCB_Q)->next = addr;

					printf("(Insert_PCB) Assigned lower position in Priority Queue.\n");
				} else { // found position was front of queue
					addr->prev = *PCB_Q;
					addr->next = NULL;
					(*PCB_Q)->next = addr;
					*PCB_Q = addr;
					printf("(Insert_PCB) Assigned to front of Priority Queue.\n");
				}
				returnInt = 2; // PCB placed inside Queue
			}
		} else if (method == 1) { // Insert at end of Queue
			//printf("(Insert_PCB) Insert Method 1: Non-priority Queue\n");
			if (*PCB_Q == NULL) {
				//printf("(Insert_PCB) Queue passed is empty\n");
				//printf("(Insert_PCB) Adding PCB to front of Queue\n");
				*PCB_Q = addr;
				(*PCB_Q)->next = NULL;
				(*PCB_Q)->prev = NULL;
				returnInt = 1; // PCB Inserted
			} else {
				//printf("(Insert_PCB) Queue passed is not empty\n");
				//printf("(Insert_PCB) Finding end of Queue\n");
				while ((*PCB_Q)->prev != NULL) {
					*PCB_Q = (*PCB_Q)->prev;
				}
				addr->next = *PCB_Q;
				addr->prev = NULL;
				(*PCB_Q)->prev = addr;
				returnInt = 2; // PCB placed inside Queue
			}
		} else {
			returnInt = -1; // incorrect method
		}
	} else {
		returnInt = -2; // incorrect addr
	}
	if (returnInt > 0) { // re-point to the front of the queue
		//printf("(Insert_PCB) Reassigning front of queue\n");
		while((*PCB_Q)->next != NULL){
			count++;
			*PCB_Q = (*PCB_Q)->next;
			if (count > 40){
				//printf("(Insert_PCB) Breaking insertion of PCB\n");
				break;
			}
		}
	}
	return returnInt;
}

/*
	Removes PCB from a queue.
	Values returned:
	 0: PCB Deleted from queue
	-1: PCB not found in specified queue
*/
int Remove_PCB(pcb **PCB_Q, pcb *addr) {
	int returnInt;
	if (addr != NULL) {
		if (addr->next == NULL) { // front of the queue
			*PCB_Q = addr->prev;
			(*PCB_Q)->next = NULL;
			addr->prev = NULL;
			returnInt = 0;
		} else {
			addr->next->prev = addr->prev;
			addr->prev->next = addr->next;
			addr->next = NULL;
			addr->prev = NULL;
			returnInt = 0;
		}
	} else {
		returnInt = -1; // wrong address
	}
	return returnInt;
}

void show(char whatToShow[9]) {
	pcb * temp = PCB_list;
	printf("NAME      TYPE STATE SUSPEND PRIORITY\n");
	printf("=====================================\n");
	if (strcmp(whatToShow, "free") == 0) {
		//printf("Printing all free PCBs\n");
		while (temp != NULL && temp->type == FREE){
			printf("%s     %d    %d     %d      %d  \n", temp->procname,temp->type,temp->state,temp->suspend,temp->priority);
			temp = temp->chain;
		}
	} else if (strcmp(whatToShow, "all") == 0) {
		//printf("Printing all PCBs\n");
		while (temp != NULL){
			if (temp->type == APPLICATION_PROCESS || temp->type == SYSTEM_PROCESS){
				printf("%s     %d    %d     %d      %d       \n", temp->procname,temp->type,temp->state,temp->suspend,temp->priority);
			}
			temp = temp->chain;
		}
	} else if (strcmp(whatToShow, "system") == 0){
		while (temp != NULL){
			if (temp->type == SYSTEM_PROCESS){
				printf("%s     %d    %d     %d      %d  \n", temp->procname,temp->type,temp->state,temp->suspend,temp->priority);
			}
			temp = temp->chain;
		}
	} else if (strcmp(whatToShow, "application") == 0){
		while (temp != NULL){
			if (temp->type == APPLICATION_PROCESS){
				printf("%s     %d    %d     %d      %d  \n", temp->procname,temp->type,temp->state,temp->suspend,temp->priority);
			}
			temp = temp->chain;
		}
	} else if (strcmp(whatToShow, "suspended") == 0){
		while (temp != NULL){
			if (temp->suspend == SUSPENDED){
				printf("%s     %d    %d     %d      %d  \n", temp->procname,temp->type,temp->state,temp->suspend,temp->priority);
			}
			temp = temp->chain;
		}
	} else if (strcmp(whatToShow, "ready") == 0){
		temp = ReadyQ;
		if (temp == NULL){
			printf("(Show) There is nothing in the Ready Queue\n");
		}
		while (temp != NULL){
			printf("%s     %d    %d     %d      %d  \n", temp->procname,temp->type,temp->state,temp->suspend,temp->priority);
			temp = temp->prev;
		}
	} else if (strcmp(whatToShow, "init") == 0){
		temp = IO_InitQ;
		while (temp != NULL){
			printf("%s     %d    %d     %d      %d  \n", temp->procname,temp->type,temp->state,temp->suspend,temp->priority);
			temp = temp->prev;
		}
	}
}

int initPCBs(){
	PCB_list = &pcb1;
	pcb1.chain = &pcb2;
	pcb1.chain = &pcb2;
	pcb2.chain = &pcb3;
	pcb3.chain = &pcb4;
	pcb4.chain = &pcb5;
	pcb5.chain = &pcb6;
	pcb6.chain = &pcb7;
	pcb7.chain = &pcb8;
	pcb8.chain = &pcb9;
	pcb9.chain = &pcb10;
	pcb10.chain = &pcb11;
	pcb11.chain = &pcb12;
	pcb12.chain = &pcb13;
	pcb13.chain = &pcb14;
	pcb14.chain = &pcb15;
	pcb15.chain = &pcb16;
	pcb16.chain = &pcb17;
	pcb17.chain = &pcb18;
	pcb18.chain = &pcb19;
	pcb19.chain = &pcb20;
	pcb20.chain = NULL;
	pcb1.type = FREE;
	pcb2.type = FREE;
	pcb3.type = FREE;
	pcb4.type = FREE;
	pcb5.type = FREE;
	pcb6.type = FREE;
	pcb7.type = FREE;
	pcb9.type = FREE;
	pcb10.type = FREE;
	pcb11.type = FREE;
	pcb12.type = FREE;
	pcb13.type = FREE;
	pcb14.type = FREE;
	pcb15.type = FREE;
	pcb16.type = FREE;
	pcb17.type = FREE;
	pcb18.type = FREE;
	pcb19.type = FREE;

/*
	pcb *pcb1;
	pcb *pcb2, *pcb3, *pcb4, *pcb5, *pcb6, *pcb7, *pcb8, *pcb9, *pcb10;
	pcb *pcb11, *pcb12, *pcb13, *pcb14, *pcb15, *pcb16, *pcb17, *pcb18, *pcb19, *pcb20;
	printf("made pcbs\n");
	PCB_list = &pcb1;
	printf("assigned list\n");
	pcb1->chain = &pcb2;
	pcb2->chain = &pcb3;
	pcb3->chain = &pcb4;
	pcb4->chain = &pcb5;
	pcb5->chain = &pcb6;
	pcb6->chain = &pcb7;
	pcb7->chain = &pcb8;
	pcb8->chain = &pcb9;
	pcb9->chain = &pcb10;
	pcb10->chain = &pcb11;
	pcb11->chain = &pcb12;
	pcb12->chain = &pcb13;
	pcb13->chain = &pcb14;
	pcb14->chain = &pcb15;
	pcb15->chain = &pcb16;
	pcb16->chain = &pcb17;
	pcb17->chain = &pcb18;
	pcb18->chain = &pcb19;
	pcb19->chain = &pcb20;
	pcb20->chain = NULL;
	printf("assigned chains\n");
 */
	return 1;

}
