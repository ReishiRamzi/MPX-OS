/*  file:  ManageComs.c
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
 void Load(char *name, int priority){
	pcb * pcb_add;
	pcb_add = Get_PCB(PCB_list);
    if (pcb_add != NULL){
        if (priority != NULL){
            // THIS REQUIRES THE load.c SUPPORT PROCEDURE FOR THIS MODULE
            Build_PCB(pcb_add, name, APPLICATION_PROCESS, READY, SUSPENDED, priority, (unsigned *) _CS, (unsigned *) test5);
            Insert_PCB(&ReadyQ,pcb_add,0);
        } else {
            // THIS REQUIRES THE load.c SUPPORT PROCEDURE FOR THIS MODULE
            Build_PCB(pcb_add, name, APPLICATION_PROCESS, READY, SUSPENDED, DEFAULT_PRIORITY, (unsigned *) _CS, (unsigned *) test5);
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
         pcb_addr->suspend = NOT_SUSPENDED;
     } else {
         printf("(Resume) %d was not found.\n", name);
     }
 }

 // Assigns the requested information to a PCB then sets it to NOT_SUSPENDED
 // This can be rewritten to essentially just be Load() but setting the suspend to NOT_SUSPENDED instead.
 void Run(char *name, int priority){
     Load(name,priority);
     Resume(name);
 }

 // Checks for a PCB by name and sets it to SUSPENDED as long as it isn't a SYSTEM_PROCESS
 void Suspend(char *name){
     pcb * pcb_add;
     pcb_add = Search_PCB(PCB_list, name);
     if (pcb_add != NULL){
         if (pcb_add->type != SYSTEM_PROCESS){
             pcb_addr->suspend = SUSPENDED;
         } else {
             printf("(Suspend) %d cannot be suspended because it is a system process.\n", name);
         }
     } else {
         printf("(Suspend) %d was not found.\n", name);
     }
 }
 // Frees the requested PCB as long as it exists.
 void Terminate(char *name){
     pcb * pcb_add;
     pcb_add = Search_PCB(PCB_list, name);
     if (pcb_add != NULL){
         Free_PCB(PCB_list, pcb_add);
     } else {
         printf("(Terminate) %d was not found.\n", name);
     }
 }

 // Sets a PCB's priority as long as it isn't a SYSTEM_PROCESS and the requested
 // priority is valid.
 void SetPriority(char *name, int priority){
     pcb * pcb_add;
     pcb_add = Search_PCB(PCB_list, name);
     if (pcb_add != NULL){
         if (pcb_add->type != SYSTEM_PROCESS){
             if (priority > -127 && priority < 127){
                 pcb_addr->priorty = priority;
             }
         } else {
             printf("(SetPriority) %d cannot have it's priority changed because it is a system process.\n", name);
         }
     } else {
         printf("(SetPriority) %d was not found.\n", name);
     }
 }

 // Dispatches one at a time, then returns control to COMHAN
 void Dispatch_CMD(){
     pcb dummy_pcb;

     /* Set cop to point to the dummy PCB that points to the first PCB in
        ReadyQ to force one-pass round robin dispatcher to start at the
        front of the ready queue                                         */

     cop = &dummy_pcb;
     cop->prev = ReadyQ;

     /* Save COMHAN's stack pointer */

     sp_save = _SP - DISP_OFFSET;

     dispatch();
 }
