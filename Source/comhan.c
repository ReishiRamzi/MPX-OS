/*
*   comhan.c
*   02/06/2019
*   COMHAN (Command Handler) is the command interface for MPX
*   Its role is to:
*   1. read a command entered via the system console keyboard
*   2. analyze the command 
*   3. execute the command
*
*/

#include "comhan.h"

void main()
{
    char buffer[BUF_SIZE];
    int buf_len;
    buf_len = BUF_SIZE;

    sys_req(CON, READ, buffer, &buf_len);
}