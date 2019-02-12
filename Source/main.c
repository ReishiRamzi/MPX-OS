#include <stdio.h>

#include "mpx.h"

// entry point 
int main ()
{
    // print booting message
    printf("... booting MPX\n\n");
    
    // execute the command handler
    comhan();

    // exit 
    return 0;
}