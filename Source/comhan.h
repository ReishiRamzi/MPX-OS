/*
*   comhan.h
*   02/06/2019
*   COMHAN (Command Handler) is the command interface for MPX
*   Its role is to:
*   1. read a command entered via the system console keyboard
*   2. analyze the command
*   3. execute the command
*
*/

/* Commands it should handle*/
// version:     print the software version number for COMHAN and MPX
// date:        display or set the system date
// directory    print a directory of the .mpx programs on disk
// stop:        stop execution of COMHAN
// help:        print help information
// prompt:      change the command handler prompt
// alias:       specify an alias for a COMHAN command

// CON specifies that the operation should use the console for IO
#define CON 1

// READ/WRITE
#define READ 1
#define WRITE 2

// define the buffer
#define BUF_SIZE 80

// we will be making system requests
extern int sys_req
(
    int op_number,
    int op_type,
    char buffer[],
    int *length
);
