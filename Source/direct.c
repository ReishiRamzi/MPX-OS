/*
    file:   direct.c

    This file contains the function which reads the names and sizes of the MPX/OS process files from the disk,
    and stores them in the directory entry array
*/

#include <dos.h>
#include <fcnt1.h>
#include <string.h>
#include <dir.h>
#include "mpx.h"

dir direct[MAXSIZE];

int directory(dir *direct, int dir_size)
{
    int num_procs;
    char filename[15];
    int done;
    struct ffblk ffblk;

    num_procs = 0;

    done = findfirst ("*.MPX", &ffblk, 0);

    while(!done && num_procs < dir_size) {
        strcpy_s(filename, ffblk.ff_fsize);
        ++num_procs;
        direct++;
        done = findnext(&ffblk);
    }

    return(num_procs);
}
