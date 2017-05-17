/*
Name: 	Joel v
		Kieran K
		
Module: IKBD

Purpose: Contains the functions related to reading mouse and keyboard input,
		 as well as the global keyboard buffer structure

Details: The main IKBD stuff is called from an assembly function which is
		 installed in place of the atari ikbd isr
*/

#ifndef TSTIKBD_H
#define TSTIKBD_H

#include "input.h"
#include "isr.h"
#include "types.h"
#include <osbind.h>

#define TRUE 1
#define FALSE 0

#define IKBD_ASCII_SIZE 0x73

#define IKBD_ISR 70 /* IKBD ISR is located at vector 70 */

#define IKBD_CTRL 0x00FFFC00	/* IKBD Control register (byte array)*/
#define IKBD_SR	0x00FFFC00	/* IKBD Status Register (byte array)*/
#define IKBD_RDR 0x00FFFC02	/* keyboard receive data register */
#define IKBD_SR_INTERRUPT_ON 0x80


#define MSB_8 0x80 /* MSB of a byte */
#define IKBD_BREAK 0x80
#define IKBD_MOUSE_THRESHOLD 0xF8

#define MOUSE_X_DEFAULT 320
#define MOUSE_Y_DEFAULT 200

/* the IKBD buffer, a queue implemented as a circular array */
struct BufferQueue
{
	UINT32 buffer[256];
	UINT8 head;
	UINT8 tail;
	UINT16 fillLevel;
    int mouseX;
    int mouseY;
};

extern struct BufferQueue ikbdBuffer;

extern UINT8 fsmCurrentState;


/* function prototypes */
void readIKBD(void);
UINT8 readRecRegister(void);
UINT8 ikbdGetAscii(UINT8 keymap);
void ikbdEnqueue(UINT32 value);
UINT32 ikbdDequeue(void);
UINT8 ikbdEmpty(void);




#endif