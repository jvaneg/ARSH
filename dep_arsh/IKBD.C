/*
Name: 	Joel v
		Kieran K
		
Module: IKBD
*/

#include "ikbd.h"

/* the key buffer */
struct BufferQueue ikbdBuffer =
{
	{0},
	1,
	0,
	0,
    MOUSE_X_DEFAULT,
    MOUSE_Y_DEFAULT
};


/* 
ascii table indexed by keymap code
ONLY LOWERCASE
see scancodes.txt for reference 
*/
const UINT8 asciiLookup[IKBD_ASCII_SIZE] = {
	0x00, /* 00 | DNE */
	0x1B, /* 01 | ESC */
	0x31, /* 02 | 1 */
	0x32, /* 03 | 2 */
	0x33, /* 04 | 3 */
	0x34, /* 05 | 4 */
	0x35, /* 06 | 5 */
	0x36, /* 07 | 6 */
	0x37, /* 08 | 7 */
	0x38, /* 09 | 8 */
	0x39, /* 0A | 9 */
	0x30, /* 0B | 0 */
	0x2D, /* 0C | - */
	0x3D, /* 0D | = */
	0x08, /* 0E | BKSP */
	0x09, /* 0F | TAB */
	0x71, /* 10 | Q */
	0x77, /* 11 | W */
	0x65, /* 12 | E */
	0x72, /* 13 | R */
	0x74, /* 14 | T */
	0x79, /* 15 | Y */
	0x75, /* 16 | U */
	0x69, /* 17 | I */
	0x6F, /* 18 | O */
	0x70, /* 19 | P */
	0x5B, /* 1A | [ */
	0x5D, /* 1B | ] */
	0x0D, /* 1C | RTRN */
	0x00, /* 1D | CTRL */
	0x61, /* 1E | A */
	0x73, /* 1F | S */
	0x64, /* 20 | D */
	0x66, /* 21 | F */
	0x67, /* 22 | G */
	0x68, /* 23 | H */
	0x6A, /* 24 | J */
	0x6B, /* 25 | K */
	0x6C, /* 26 | L */
	0x3B, /* 27 | ; */
	0x27, /* 28 | ' */
	0x60, /* 29 | EURO ' */
	0x00, /* 2A | LSHFT */
	0x5C, /* 2B | \ */
	0x7A, /* 2C | Z */
	0x78, /* 2D | X */
	0x63, /* 2E | C */
	0x76, /* 2F | V */
	0x62, /* 30 | B */
	0x6E, /* 31 | N */
	0x6D, /* 32 | M */
	0x2C, /* 33 | , */
	0x2E, /* 34 | . */
	0x2F, /* 35 | / */
	0x00, /* 36 | RSHFT */
	0x00, /* 37 | DNE */
	0x00, /* 38 | ALT */
	0x20, /* 39 | SPC */
	0x00, /* 3A | CAPS */
	0x00, /* 3B | F1 */
	0x00, /* 3C | F2 */
	0x00, /* 3D | F3 */
	0x00, /* 3E | F4 */
	0x00, /* 3F | F5 */
	0x00, /* 40 | F6 */
	0x00, /* 41 | F7 */
	0x00, /* 42 | F8 */
	0x00, /* 43 | F9 */
	0x00, /* 44 | F10 */
	0x00, /* 45 | DNE */
	0x00, /* 46 | DNE */
	0x00, /* 47 | HOME */
	0x00, /* 48 | UP ARW */
	0x00, /* 49 | DNE */
	0x2D, /* 4A | NUM - */
	0x00, /* 4B | LFT ARW */
	0x00, /* 4C | DNE */
	0x00, /* 4D | RT ARW */
	0x2B, /* 4E | NUM + */
	0x00, /* 4F | DNE */
	0x00, /* 50 | DN ARW */
	0x00, /* 51 | DNE */
	0x00, /* 52 | INSRT */
	0x7F, /* 53 | DEL */
	0x00, /* 54 | DNE */
	0x00, /* 55 | DNE */
	0x00, /* 56 | DNE */
	0x00, /* 57 | DNE */
	0x00, /* 58 | DNE */
	0x00, /* 59 | DNE */
	0x00, /* 5A | DNE */
	0x00, /* 5B | DNE */
	0x00, /* 5C | DNE */
	0x00, /* 5D | DNE */
	0x00, /* 5E | DNE */
	0x00, /* 5F | DNE */
	0x00, /* 60 | DNE */
	0x00, /* 61 | UNDO */
	0x00, /* 62 | HELP */
	0x28, /* 63 | NUM ( */
	0x29, /* 64 | NUM ) */
	0x2F, /* 65 | NUM / */
	0x2A, /* 66 | NUM * */
	0x37, /* 67 | NUM 7 */
	0x38, /* 68 | NUM 8 */
	0x39, /* 69 | NUM 9 */
	0x34, /* 6A | NUM 4 */
	0x35, /* 6B | NUM 5 */
	0x36, /* 6C | NUM 6 */
	0x31, /* 6D | NUM 1 */
	0x32, /* 6E | NUM 2 */
	0x33, /* 6F | NUM 3 */
	0x30, /* 70 | NUM 0 */
	0x2E, /* 71 | NUM . */
	0x0D  /* 72 | NUM ENTR */
		
};



volatile 		UINT8* const ikbdControl = IKBD_CTRL; /* IKBD control register */
volatile const 	UINT8* const ikbdStatus = IKBD_SR; /*IKBD status register, const because its read only */
volatile const 	UINT8* const ikbdRDR = IKBD_RDR; /*IKBD received register, const because its read only */


UINT8 fsmCurrentState = 0; /* current state of the finite state machine used by the IKBD isr*/



/*
Name: readIKBD
Purpose: reads from the IKBD received register, does a little processing to
		 combine the keymap read with the associated ascii, then puts it into the
		 IKBD buffer
Details: ignores mouse input through the use of a finite state machine
		 This function is meant to be called by an assembly routine
*/
void readIKBD(void)
{
	UINT8 interruptStatus = *ikbdStatus;
	UINT8 inputPacket;
	UINT8 ascii;
	UINT32 fullCode;
	
	inputPacket = *ikbdRDR;
	interruptStatus &= MSB_8;
	
	if(interruptStatus != IKBD_SR_INTERRUPT_ON)
	{
		while(TRUE); /*hardware failure - forced to hang */
	}
	else
	{		 
		if(fsmCurrentState == 0) /* if we're not midway through a mouse triplet */
		{
			if(inputPacket < IKBD_MOUSE_THRESHOLD) /* if its a keyboard packet */
			{
				if( (inputPacket & MSB_8) != IKBD_BREAK ) /* if its a make code key */
				{
					ascii = ikbdGetAscii(inputPacket);
					
					fullCode = (UINT32) inputPacket;
					fullCode = fullCode << 16;
					fullCode |= ascii;
					
					ikbdEnqueue(fullCode);
				}
			}
			else /* its a mouse packet */
			{
                fullCode = (UINT32) inputPacket;
				fullCode = fullCode << 16;
                ikbdEnqueue(fullCode);
				fsmCurrentState++;
			}
		}
		else /* we're midway through a mouse triplet */
		{
			if(fsmCurrentState >= 2)
			{
                ikbdBuffer.mouseY += (int) ((signed char) inputPacket);
                if(ikbdBuffer.mouseY > 400)
                {
                    ikbdBuffer.mouseY = 400;
                }
                else if(ikbdBuffer.mouseY < 0)
                {
                    ikbdBuffer.mouseY = 0;
                }
				fsmCurrentState = 0;
			}
			else
			{
                ikbdBuffer.mouseX += (int) ((signed char) inputPacket);
                if(ikbdBuffer.mouseX > 640)
                {
                    ikbdBuffer.mouseX = 640;
                }
                else if(ikbdBuffer.mouseX < 0)
                {
                    ikbdBuffer.mouseX = 0;
                }
				fsmCurrentState++;
			}
		}
	}
	
	return;
}


/*
Name: readRecRegister
Purpose: reads the IKBD 6850 received register
Return value: inputPacket - the input packet read from the register, type UINT8
*/
UINT8 readRecRegister(void)
{
	UINT8 inputPacket = *ikbdRDR;
	return inputPacket;
}

/*
Name: ikbdGetAscii
Purpose: looks up the ascii value associated with an IKBD keymap code
Input: IKBD keymap code, type UINT8
Return value: ASCII code associated with keymap (if one exists), type UINT8
*/
UINT8 ikbdGetAscii(UINT8 keymap)
{
	if(keymap >= IKBD_ASCII_SIZE)
	{
		return 0;
	}
	else
	{
		return asciiLookup[keymap];
	}
}


/*
Name: ikbdEnqueue
Purpose: adds a keymap code + ascii value longword into the IKBD buffer
Input: combined keymap code + ascii value, type UINT32
*/
void ikbdEnqueue(UINT32 value)
{
	ikbdBuffer.tail += 1;
	ikbdBuffer.buffer[ikbdBuffer.tail] = value;
	ikbdBuffer.fillLevel++;
	
	return;
}

/*
Name: ikbdDequeue
Purpose: removes a keymap code + ascii value longword from the IKBD buffer
Return value: combined keymap code + ascii value, type UINT32
*/
UINT32 ikbdDequeue(void)
{
	UINT32 retValue = ikbdBuffer.buffer[ikbdBuffer.head];
	ikbdBuffer.head += 1;
	ikbdBuffer.fillLevel--;
	
	return retValue;
}

/*
Name: ikbdEmpty
Purpose: checks if the IKBD buffer is empty
Return value: whether or not the IKBD buffer is empty, type UINT8
			  0 - not empty
			  not 0 - empty
*/
UINT8 ikbdEmpty(void)
{
	return (UINT8) !ikbdBuffer.fillLevel;
}