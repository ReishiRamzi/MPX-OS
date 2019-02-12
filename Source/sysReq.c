/*
    file: sysReq.c

    implements the MPX system request function

    parameters: 
        number  - a device or exit code
        type    - request type: read, write, wait, signal
        s       - address of read/write buffer
        length  - address of buffer length variable
    
    return value: none

*/

void sys_req (int number, int type, char *s, int *length)
{
    number = number; // avoid an "unused variable" warning
    
    type = type;

    // read a string from the keyboard
    gets(s);

    // get its length
    *length = strlen(s);
}