/*  file:  version.c
 *
 * This file returns an the current version of
 * the MPX OS.
 */

#include <stdio.h>

#include "mpx.h"

char* curVersion = "0.1";

char* version(){
   return curVersion;
}
