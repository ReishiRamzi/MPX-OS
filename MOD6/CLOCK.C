/***********************************************************************
*
*	Name:   clock.c
*
*	Purpose:  provides clock functions
*
* 	Procedures In Module:
*                     clock_open()
*					  clock_int()
*					  clock_close()
*					  stop_clock()
*					  start_clock()
*					  set_clock(val)
*					  read_clock(val)
****************************************************************************/

#include <stdio.h>
#include <dos.h>
#include "mpx.h"

#define IMR 0x21
#define IRQ0 0x01
#define CLOCK_ENABLE (0xff-IRQ0)
#define CLOCK_DISABLE (0x1)

long int count;
void interrupt (*vect8)();

void clock_open(){
	int imr;
	// get current DOS vector at 8
	vect8 = getvect(0x8);
	// set vector at 8 to clock interrupt
	setvect(0x8, &clock_int);
	// push mask onto 8259
	// Set to interrupt - 00110110
	outportb(0x43, 0x36);
	outportb(0x40, 0);
	outportb(0x40, 0);
	// set count to 0
	count = 0;
	// read current IMR
	imr = inportb(IMR);
	// clear IRQ0 (clock on imr)
	imr = imr & CLOCK_ENABLE;
	// set new IMR
	outportb(IMR, imr);
}

void interrupt clock_int(){
	static int ticks;
	disable();
	count++;
	outportb(0x20, 0x20);
	enable();
}

void clock_close(){
	setvect(0x8,vect8);
	exit();
}

void Stop_Clock(){
	int imr;
	// read current IMR
	imr = inportb(IMR);
	// clear IRQ0 (clock on imr)
	imr = imr | CLOCK_DISABLE;
	// set new IMR
	outportb(IMR, imr);
}

void Start_Clock(){
	int imr;
	// read current IMR
	imr = inportb(IMR);
	// clear IRQ0 (clock on imr)
	imr = imr & CLOCK_ENABLE;
	// set new IMR
	outportb(IMR, imr);
}

void Set_Clock(int hours, int minutes, int seconds){
	long int tempTicks;
	//printf("(Set_Clock) %d:%d:%d\n",hours,minutes,seconds);
	tempTicks = 0L;
	//printf("(Set_Clock) Reset Ticks : %ld\n",tempTicks);
	tempTicks += ((long)seconds * 18L);
	//printf("(Set_Clock) After Seconds : %ld\n",tempTicks);
	tempTicks += ((long)minutes * 60L) * 18L;
	//printf("(Set_Clock) After Minutes : %ld\n",tempTicks);
	tempTicks += ((((long)hours * 60L) * 60L) * 18L);
	//printf("(Set_Clock) After Hours : %ld\n",tempTicks);
	count = tempTicks;
	PrintClock();
	//Read_Clock();
}

void Read_Clock(){
	long int seconds;
	long int minutes;
	long int hours;
	long int realCount;
	realCount = count * 1.01162791L;
	printf("(Read_Clock) Tick converted to realCount after compensating for extra .207 per second tick rate.\n");
	hours = (((realCount/18L)/60L)/60L);
	printf("(Read_Clock) Hours: %ld\n",hours);
	minutes = (realCount - (((hours * 60L) * 60L) * 18L));
	minutes =  ((minutes/18L)/60L);
	printf("(Read_Clock) Minutes: %ld\n",minutes);
	seconds = (realCount - ((((hours * 60L)*60L)*18L) + ((minutes*60L)*18L)));
	seconds = seconds/18L;
	printf("(Read_Clock) Seconds: %ld\n",seconds);
	printf("Current Time: %ld:%ld:%ld\n",hours,minutes,seconds);
}

void ClockCom(char *arg1, char *arg2, char *arg3){
	if (strcmp(arg1, "stop") == 0){
		Stop_Clock();
	} else if (strcmp(arg1, "start") == 0){
		Start_Clock();
	} else if (arg1 != NULL && arg2 != NULL && arg3 != NULL){
		Set_Clock(atoi(arg1), atoi(arg2), atoi(arg3));
	} else if (arg1 == NULL){
		Read_Clock();
	} else {
		printf("(ClockCom) Invalid argument\n");
	}
}

void PrintClock(){
	printf("Clock Ticks - %ld\n", count);
}