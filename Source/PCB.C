/*
 *    file:  pcb.c
 *
 *    This file contains the functions related to process control
 *    blocks.
 */

#include "mpx.h"

#include "malloc.h"

pcb * PCB_list; /* Pointer to first PCB */
pcb * ReadyQ; /* Pointer to priority queue of PCBs */
pcb * IO_InitQ; /* Pointer to FIFO queue of PCBS */
int numPCBs = 20;

/*
    Returns the address of a pcb with the name of pcbname[9].
    If the address isnt found (name doesnt exist), addr returns null (\0)
*/
pcb* Search_PCB(pcb *pcbPtr, char *pcbname[9]) {
    pcb *addr = '\0';
    pcb *temp = pcbPtr;
    while (temp != '\0') {
        if (strcmp(temp->procname, pcbname) == 0) {
			addr = temp->loadaddr;
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
    pcb *addr = '\0';
    pcb *temp = pcbPtr;
    while (temp != '\0') {
        if (temp->type == FREE) {
			addr = temp->loadaddr;
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
    while (temp != '\0') {
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
*/
int Build_PCB(pcb *addr, char *name, int type, int state, int suspend) {
	int returnInt = 0;
	int addrCheck = 0;
	pcb *temp = PCB_list;
	while (temp != '\0') { // make sure the addr exists
		if (strcmp(temp->loadaddr, addr) == 0) {
			addrCheck = 1; // change to 1 if addr exists
			break;
		}
		temp = temp->chain;
	}
	if (addrCheck == 1) {
		if (suspend == 0 || suspend == 1) {
			if (state > -1 && state < 3) {
				if (type > -1 && type < 3) { // if all parameters are valid,
					temp->suspend = suspend; // theyre applied to the PCB
					temp->state = state;
					temp->type = type;
					strcpy(temp->procname, name);
                    returnInt = 1;
                } else { // type is invalid
                    returnInt = -2;
                }
            } else { // state is invalid
                returnInt = -3;
            }
        } else { // suspend is invalid
            returnInt = -4;
        }
    } else { // address is invalid
        returnInt = -1;
    }
    return returnInt;
}

/*
    Inserts PCB into a queue.
    Values returned:
     1: PCB Inserted
    -1: Incorrect method
    -2: Incorrect addr
*/
int Insert_PCB(pcb *PCB_Q, pcb *addr, int method) {
    int returnInt;
    pcb *temp = PCB_list;
    pcb *tempQ = PCB_Q;
    while (temp != '\0') { // make sure the addr exists
        if (strcmp(temp->loadaddr, addr) == 0) {
            break;
        }
        temp = temp->chain;
    }
    if (temp != '\0') {
        if (method == 0) { // Insert into Priority Queue
            if (PCB_Q == '\0') {
                PCB_Q = temp;
                temp->next = '\0';
                temp->prev = '\0';
                returnInt = 1; // PCB Inserted
            } else {
                while (tempQ->prev != '\0' && tempQ->priority >= temp->priority) {
                    tempQ = tempQ->prev;
                }
                tempQ->prev->next = temp;
                temp->prev = tempQ->prev;
                temp->next = tempQ;
                tempQ->prev = temp;
            }
        } else if (method == 1) { // Insert at end of Queue
            if (PCB_Q == '\0') {
                PCB_Q = temp;
                temp->next = '\0';
                temp->prev = '\0';
                returnInt = 1; // PCB Inserted
            } else {
                while (tempQ->prev != '\0') {
                    tempQ = tempQ->prev;
                }
                temp->next = tempQ;
                temp->prev = '\0';
                tempQ->prev = temp;
            }
        } else {
            returnInt = -1; // incorrect method
        }
    } else {
        returnInt = -2; // incorrect addr
    }
    if (returnInt > 0) { // re-point to the front of the queue
        tempQ = PCB_Q;
        while (tempQ->next != '\0') {
            PCB_Q = tempQ->next;
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
int Remove_PCB(pcb *PCB_Q, pcb *addr) {
    int returnInt;
    pcb *tempQ = PCB_Q;
    while (tempQ != '\0') { // make sure the addr exists
        if (strcmp(tempQ->loadaddr, addr) == 0) {
            break;
        }
        tempQ = tempQ->prev;
    }
    if (tempQ != '\0') {
        if (tempQ->next == '\0') { // front of the queue
            PCB_Q = tempQ->prev;
            tempQ->prev->next = '\0';
            tempQ->prev = '\0';
            returnInt = 0;
        } else {
            tempQ->next->prev = tempQ->prev;
            tempQ->prev->next = tempQ->next;
            tempQ->next = '\0';
            tempQ->prev = '\0';
            returnInt = 0;
        }
    } else {
        returnInt = -1; // wrong address
    }
    return returnInt;
}

void show(char whatToShow) {
    pcb * temp = PCB_list;
    int i = 1;
    if (strcmp(whatToShow, "free") == 0) {
        while (temp != '\0') {
            printf("PCB %s FREE", i);
            i++;
            temp = temp->chain;
        }
    }
}

void initPCBs() {


    pcb *pcb1;
    pcb *pcb2, *pcb3, *pcb4, *pcb5, *pcb6, *pcb7, *pcb8, *pcb9, *pcb10;
    pcb *pcb11, *pcb12, *pcb13, *pcb14, *pcb15, *pcb16, *pcb17, *pcb18, *pcb19, *pcb20;
	PCB_list = &pcb1;
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
    pcb20->chain = '\0';
}