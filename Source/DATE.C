/*  file:  date.c
 *
 * This file allows the user to check the current date as well as update
 * the date.
 */
 #include <stdio.h>
 #include "mpx.h"

 char* date = "02/20/2019";

 char* getDate(){
     return date;
 }

 void upDate(char newDate[10]){
     int i;
     int true = 1;
     for (i = 0; i < 10; i++){
	 if (i == 2 || i == 5){
	     if (newDate[i] != '/'){
		 true = 0;
	     }
	 } else {
	     if (isdigit(newDate[i]) == 0){
		 true = 0;
	     }
	 }
     }
     if (newDate[10] != NULL){
	 true = 0;
     }
     if (true != 0){
	 date = newDate;
     }
 }
