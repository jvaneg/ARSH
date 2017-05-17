/*
Name: 	Joel v
		Kieran K
		
Module: Input
*/

#include "input.h"


/*
Name: inputPending
Purpose: determines whether or not keyboard input is
		 available for reading.
		 
Return value: whether or not there is pending input, type UINT8

Details: return value works like a bool, 
		 returns -1 if true,
		 returns 0 if false
*/
UINT8 inputPending(void)
{
	UINT8 inputPending;
	int oldIpl;
	long oldSsp;
	
    oldIpl = maskInterrupt(7);
	
	inputPending = !ikbdEmpty();

    maskInterrupt(oldIpl);
	
	return inputPending;
}


/*
Name: readChar
Purpose: reads a key from the keyboard
		 
Return value: ASCII value of the character read from the keyboard, type UINT8
*/
UINT8 readChar(void)
{
	UINT8 readChar;
	int oldIpl;
	long oldSsp;
	
    oldIpl = maskInterrupt(7);
	
	readChar = ikbdDequeue();
	
    maskInterrupt(oldIpl);
	
	return readChar;
}


/*
Name: readKeyMap
Purpose: reads a key from the keyboard
		 
Return value: the keymap of the key read from the keyboard, type UINT8
*/
UINT8 readKeyMap(void)
{	
	UINT8 keymap;
	int oldIpl;
	long oldSsp;
	
	oldIpl = maskInterrupt(7);
    
	keymap = ikbdDequeue() >> 16;
    
    maskInterrupt(oldIpl);
	
	return keymap;
}


/*
Name: getTime
Purpose: gets the current time from the 70hz hardware clock
		 
Return value: the current time, type UINT32

Details: the timer long is located at address 0x462
		 to access the timer, you must first be in supervisor mode
*/
UINT32 getTime(void)
{
	UINT32 *timer = (UINT32*) 0x462;
	UINT32 currentTime;
	long oldSsp;
	
	oldSsp = Super(0);
	currentTime = *timer;
	Super(oldSsp);
	
	return currentTime;
}


/*
Name: getVideoBase

Purpose: gets the address start of the frame buffer from the video base register

Return Value: videoBase - the address of the start of the frame buffer, type UINT32*

Details: 	the video base register high byte is located at 0x00FF8201
            the video base register middle byte is located at 0x00FF8203
            the video base register low byte is always 00
			requires supervisor mode to access the address of these registers
*/
UINT32* getVideoBase()
{
	UINT8* videoBaseHighRegister = (UINT8*) 0x00FF8201;
    UINT8* videoBaseMidRegister = (UINT8*) 0x00FF8203;
    UINT8 highByte;
    UINT8 midByte;
	UINT32 videoBase;
	long oldSsp;
	
	oldSsp = Super(0);
	highByte = *videoBaseHighRegister;
    midByte = *videoBaseMidRegister;
	Super(oldSsp);
    
    videoBase = ( (UINT32) highByte << 16);
    videoBase |= ( (UINT32) midByte << 8);
	
	return (UINT32*) videoBase;
}


/*
Name: setVideoBase

Purpose: sets the address start of the frame buffer in the video base register to the
		 specified address

Input: newVideoBase - the new start address of the new frame buffer, type UINT32*

Details: 	the video base register high byte is located at 0x00FF8201
            the video base register middle byte is located at 0x00FF8203
            the video base register low byte is always 00
			requires supervisor mode to access the address of this registers
*/
void setVideoBase(UINT32* newVideoBase)
{
	UINT16 topMidWord;
	UINT32 videoBase = (UINT32) newVideoBase;
	long oldSsp;
	
	videoBase = videoBase >> 8;
	topMidWord = (UINT16) videoBase;
	
	oldSsp = Super(0);
	setVideoBaseAsm(topMidWord);
	Super(oldSsp);
	
	return;
}