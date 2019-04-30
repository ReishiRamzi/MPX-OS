/*  file:  version.c
 *
 * This file returns an the current version of
 * the MPX OS.
 */

#include <stdio.h>

#include "mpx.h"

// Current version of the operating system.
char* curVersion = "0.1";

// Returns the current version
char* version(){
   return curVersion;
}
