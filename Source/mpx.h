/*
 *     file:    mpx.h
 *
 *     Header file for the MPX Operating System.
 *
 *     This file contains constant, structure and function
 *     prototypes for the MPX Operating System
 */

/* MPX System request numbers. */

#define  EXIT_CODE 0  /* Process requesting termination. code.    */
#define  CON  1       /* The console device - keyboard & monitor. */
#define  PRT  2       /* The printer device - LPT1.               */
#define  COM  3       /* The serial port - COM1.                  */

/* MPX System request types. */

#define  READ   0  /* Read from device. */
#define  WRITE  1  /* Write to device.  */
#define  WAIT   2  /* Semaphore P operation for device. */
#define  SIGNAL 3  /* Semaphore V operation for device. */

#define MAXSIZE  20    /* Size of the directory array. */
static int NUM_CMDS = 10;   // REMEMBER TO CHANGE WHEN NEW CMDS ADDED
struct dirstruct {         /* Data type for a directory entry.        */
	char dirnam[9];        /* The name of a .mpx file.         */
	int  dirsiz;           /* The size of the file (in bytes). */
};

typedef struct dirstruct dir;  /* Use dir as the data typer name.     */

/* PCB definitions for type, state, and suspend */
/* TYPE */
#define FREE                0
#define APPLICATION_PROCESS 1
#define SYSTEM_PROCESS      2
/* STATE */
#define READY   0
#define RUNNING 1
#define BLOCKED 2
/* SUSPEND */
#define NOT_SUSPENDED 0
#define SUSPENDED     1
/* MAX PCBS */
#define MAX_PCBS 20

struct pcbstruct {           /* Data type for a process control block */
	struct pcbstruct *chain; // points to next pcb in chain
	struct pcbstruct *next;  // points to next pcb in queue
	struct pcbstruct *prev;  // points to prev pcb in queue
	char procname[9];       // name of process limited to 9 chars
	int type;               // Possible values: FREE (0),
							 // SYSTEM_PROCESS (1), APPLICATION_PROCESS(2).
	int priority;           // Range from -126 to +126 for app processes
							 // and -128 to +127 for system processes.
	int state;              // Possible values: READY (0), RUNNING(1),
							 // BLOCKED (2).
	int suspend;            // Possible values: NOT_SUSPENDED(0), SUSPENDED(1)
	int *stack_ptr;          // Pointer to top of stack to be restored when
							 // process will next be dispatched.
	int *stack[400];         // Process stack area.
	struct pcbstruct *loadaddr;            // Address of mem allocated for loading the proc.
    //^ change in the future
	int mem_size;            // Size of mem allocated for process.
};

typedef struct pcbstruct pcb; /* use pcb as the data type name for pcbstruct */

/* Function prototypes. */

void comhan(void);                    /* The MPX/OS command handler.  */
void sys_req(int,int,char *,int *);   /* MPX system request function. */
int  directory(dir *, int);           /* Support function to load the */
					                  /* directory array.             */
int quit();                           /* MPX quit function.           */
char* version();                      /* Check current MPX version    */
void alias(char *aliasArray[], char *arguments[], int index); /* make an alias for commands */
int matchCommand(char *array[], int index);  /* Takes an array of cmds and matches
                                                command based on index   */
char* changePrompt(char *currPrompt, char *args[]);
/*
*	PCB function prototypes
*/
int Allocate(char *name, char *type, char *state, char *suspend, char *priority);
int Free(char *name);
pcb* Get_PCB(pcb *pcbPtr);
pcb* Search_PCB(pcb *pcbPtr, char *pcbname[9]);
int Free_PCB(pcb *pcbListPtr, pcb *addr);
int Build_PCB(pcb *addr, char *name, int type, int state, int suspend, int priority);
int Insert_PCB(pcb *PCB_Q, pcb *addr, int method);
int Remove_PCB(pcb *PCB_Q, pcb *addr);
void show (char whatToShow[9]);
int initPCBs();
/*
 *   Global variable EXTERN directives.
 *
 *       These extern declarations allow the variables to be
 *       accessed from any source code file which includes
 *       this header file.  The memory space for the variables
 *       is declared in a *.c file.
 */
extern unsigned * sys_stack_ptr; /* Placeholder stack ptr outside of register */

extern pcb * PCB_list; /* Pointer to first PCB */
extern pcb * ReadyQ; /* Pointer to priority queue of PCBs */
extern pcb * IO_InitQ; /* Pointer to FIFO queue of PCBS */
extern dir direct[];  /* Array of directory entries -     see direct.c */
