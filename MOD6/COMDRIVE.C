/***********************************************************************
*
*	Name:   COMDRIVE.c
*
*	Purpose:  provides I/O functionality
*
* 	Procedures In Module:
*		open
*		read
*		write
*       close
*/

#include <stdio.h>
#include <dos.h>
#include "mpx.h"

dcb com_dcb;

void dcb_init(int *com_flag);

/*
* opens the communication port
* com_flag used to determine if requested operation is complete
* returns 0 if operation correct and and com1 opened
* returns -2 if com1 already open, -3 if baud rate invalid
*/
int com_open(int *com_flag, int baud_rate){
	int imr;
	int imr_mask;
	int lcr_mask;
	int ier;
	int ier_mask;
	int mcr;
	int mcr_mask;
	int divisor;
	// if com1 already open, return -2
	if(com_flag != NULL) {
	   return -2;
	}
	if (baud_rate != 1200) {
		printf("(com_open) invalid baud rate\n");
		return -3;
	}
	else if (baud_rate == 1200) {
		divisor = 96;
		// set bit 7 in LCR to 1
		lcr_mask = inportb(0x3fb);
		lcr_mask = lcr_mask | 0x80;
		// write mask to lcr
		outportb(0x3fb,lcr_mask);
		// write LSB of divisor to 0x3f8
		outportb(0x3f8, divisor);
		// write MSB of divisor to 0x3f9 (IER)
		outportb(0x3f9, divisor);
		// clear LCR
		outportb(0x3fb, 0x03);
		// read imr
		imr = inportb(0x21);
		// set imr IRQ04 to 0
		imr_mask = imr & 0xf7;
		// write back to imr
		outportb(0x21, imr_mask);
		// set bit 3 in MCR to 1 to allow seral port interrupts
		mcr = inportb(0x3fc);
		mcr_mask = mcr | 0x08;
		outportb(0x3fc, mcr_mask);
		// enable receiver data available interrupts
		// set imr bit 0 to 1 & bit 3 to 1
		ier = inportb(0x3fb);
		ier_mask = ier | 0x09;
		// initialize dcb structure values
		dcb_init(&com_flag);
	}
	else {
		printf("(com_open) invalid baud rate\n");
		return -3;
	}
	return 0;
}

void dcb_init(int *com_flag){
	com_dcb.event_flag = com_flag;
}
/*
* reads data of max length into buffer
* returns 0 for read in progress
* returns -1 for com1 not open,
* -2 for busy, -3 for error in count ( < 1)
*/
int com_read(char far *buffer, int far *length) {

}

//
int com_write(char far *buffer, int far *length) {

}

int com_close() {

}