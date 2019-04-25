/***********************************************************************
*
*	Name:   sys_sppt.c
*
*	Purpose:  Support Routines for Modules 3 and 4 of MPX-PC
*
*	Sample Call:
*                     sys_init()
*                     sys_exit()
*
* 	Procedures In Module:
*                     sys_init - Sets up interrupt vector 60 for MPX-PC
*                     sys_exit - Resets interrupt vector 60 and exits to DOS
*
*
****************************************************************************/

#include <stdio.h>
#include <dos.h>
#include "mpx.h"

#define PARM_OFFSET 28;

pcb * cop;
//void interrupt (*sys_call)();
unsigned * sys_stack[STK_SIZE];

void interrupt (*vect60)();  /* Storage for DOS int 60h */
							 /* interrupt vector.       */

void sys_init()
{
	/* set up interrupt vector for MPX sys_calls */

	vect60 = getvect(0x60);
	setvect(0x60,&sys_call);
}


void sys_exit()
{
	/* restore interrupt vector 60 and exit */

	setvect(0x60,vect60);
	exit();
}


void interrupt dispatch()
{
	// Cop is not automatically set to ReadyQ because now it is only called by COMHAN
	// cop = ReadyQ;
	// Make sure the PCB assigned to cop is NOT_SUSPENDED before running.
	// If it reaches the end of the queue, cop will be null and end dispatch.
	while (cop->suspend != NOT_SUSPENDED){
		cop = cop->prev;
	}
	if (cop == NULL){
		//sys_exit();
		//exit();

		/* Restore Dispatch_CMD's SP */
		_SP = sp_save;

		/* Retun will restore 9 registers and execute an iret instruction,
		   returning control to the calling procedure (Dispatch_CMD)      */

		return;
	}
	printf("%d dispatched.\n", cop->procname); // NOT SURE IF THIS GOES HERE OR DISPATCH_CMD BEFORE THIS
	Remove_PCB(&ReadyQ, cop);
	cop->state = RUNNING;
	_SP = cop->stack_ptr;

}


void interrupt sys_call()
{
	struct parm {
		int op_number;
		int op_type;
		char *buffer;
		int *length;
	};

	static struct parm *parm_add;

	/* Save stack pointer for current process */
	cop->stack_ptr = _SP;

	/* Get address of sys_call parameters */
	parm_add = _SP + PARM_OFFSET;

	/* Note that you should save this parameter address
	   somewhere in the pcb as suggested below*/
	cop->parm_add = parm_add;

	/* Switch to our system stack to avoid contaminating a process's stack  */
	_SP = &sys_stack[STK_SIZE - 1];

	if (parm_add->op_number != EXIT_CODE){
		Insert_PCB(&ReadyQ, cop, 0);
		cop->state = READY;
	} else {
		cop = cop;
	}
	cop = NULL;
	dispatch();
}
