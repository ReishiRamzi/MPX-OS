/*  file:  date.c
 *
 * This file allows the user to check the current date as well as update
 * the date.
 */

 #include "mpx.h"

// default date.
 char* date = "02/20/2019";

// returns current date
 char* getDate(){
     return date;
 }

// gets a new date, checks for correct formatting.
// if formatting is correct, assigns the new date to the current date.
 void upDate(char newDate[10]){
     int i;
     int true = 1;
     for (i = 0; i < 10; i++){
    	 if (i == 2 || i == 5){
    	     if (newDate[i] != '/'){ // check if / are in correct location
        		 true = 0;
        		 printf("** date argument error - %s is an invalid date.\n", newDate);
        		 break;
    	     }
    	 } else {
    	     if (isdigit(newDate[i]) == 0){ // check digits in specific location
        		 true = 0;
        		 printf("** date argument error - %s is an invalid date.\n", newDate);
        		 break;
    	     }
    	 }
     }
     if (newDate[10] != '\0'){ // if the new date is the incorrect length
    	 true = 0;
    	 printf("** date argument error - %s is an invalid date.\n", newDate);
     }
     if (true != 0){ // set date to newdate if true remained 1
    	 date = newDate;
     }
 }
