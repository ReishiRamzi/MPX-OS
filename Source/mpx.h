/*
*
*       file: mpx.h
*       Header file for the MPX Operating System
*       This file contains constant, structure and function prototypes for the MPX OS
*       include this file in other headers for its extern variables
*
*/

/* 
    MPX system request numbers 
*/ 

// Process requesting termination code
#define EXIT_CODE 0

// the console device - keyboard & monitor
#define CON 1

// the printer device - LPT1
#define PRT 2

// the serial port - COM1
#define COM 3

/* MPX system request types */

// read from device 
#define READ 0

// write to device
#define WRITE 1

// semaphore P operation for device
#define WAIT 2

// semaphore V operation for device
#define SIGNAL 3

/* 
    Directory Structure 
*/

// size of the directory array
#define MAXSIZE 20

// data type for a directory entry
struct dirStruct
{
    // the name of a .mpx file
    char dirName[9];

    // the size of the file
    int dirSize;
};

typedef struct dirStruct dir;

/* 
    Function Prototypes 
*/

// the MPX/OS command handler
void comhan(void);

// MPX system request function
void sys_req(int, int, char *, int *);

// support function to load the directory array
int directory(dir *, int);

/* 
    Global variable EXTERN directives
        These extern declarations allow the variables to be accessed from any source code file which includes this header file. 
        The memory space for the variables is declared in a *.c file.
*/

// array of directory entries - see direct.c
extern dir direct[]; 

extern struct pcb *pcb_list;