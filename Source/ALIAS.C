/*  file:  alias.c
 *
 * This file allows the user to change the alias of a specified command
 * in the command handler
 */

#include "mpx.h"


// takes a pointer to the alias array, the command number you wish to change, and a string for the new alias
void alias (char *aliasArr[], int index, char newAlias[]){
    aliasArr[index] = newAlias;
    printf("IN ALIAS.C: %s", newAlias);
}
