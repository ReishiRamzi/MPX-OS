/*  file:  alias.c
 *
 * This file allows the user to change the alias of a specified command
 * in the command handler
 */
#include <stdio.h>
#include "mpx.h"

void alias (char *aliasArr[], int index, char *newAlias){
    aliasArr[index] = newAlias;
    printf("IN ALIAS.C: %s", newAlias);
}
