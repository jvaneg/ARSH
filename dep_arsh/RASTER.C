/*
Name: 	Joel v
		Kieran K
		
Module: Raster
*/

#include "raster.h"


/*
Name: clearScreen
Purpose: Clears the full screen (sets to white).
Input: base - Pointer to the start of the frame buffer, type UINT32*
*/
void clearScreen(UINT32* base)
{
	register UINT32 clearMask = 0x00000000;
	register int longCount;
	
	for( longCount = 0; longCount < LONGS_ON_SCREEN; longCount++)
	{
		*(base++) = clearMask;
	}
}


/*
Name: plotPixel
Purpose: Plots a single pixel at the specified coordinates (sets to black)
Input:	base - Pointer to the start of the frame buffer, type UINT8*
		x    - x part of the coordinate, type int
		y	 - y part of the coordinate, type int
*/
void plotPixel(UINT8* base, int x, int y)
{
	
	if( x >= 0 && x < SCREEN_WIDTH &&
		y >= 0 && y < SCREEN_HEIGHT )
	{
		*(base + y * BYTES_PER_ROW + (x >> 3)) |= 1 << (7 - (x & 7));
	}
}


/*
Name: plotVerticalLine
Purpose: draws a vertical line to the screen of a specified height,
		 with the top at the specified coordinate
Input:	base 	- Pointer to the start of the frame buffer, type UINT8*
		x    	- x part of the coordinate, type int
		y	 	- y part of the coordinate, type int
		height	- height of the line, type int
*/
void plotVerticalLine(UINT8* base, int x, int y, int height)
{
	int rowCount;
	
	if( x >= 0 && x < SCREEN_WIDTH &&
		y >= 0 && y < SCREEN_HEIGHT )
	{
		UINT8 bitMask = 1 << (7 - (x & 7));
		UINT8* currentByte = (base + (y * BYTES_PER_ROW) + (x >> 3));
		
		for(rowCount = 0; rowCount < height && y < SCREEN_HEIGHT; rowCount++)
		{
			*currentByte |= bitMask;
			currentByte += BYTES_PER_ROW;
			y++;
		}
	}
}


/*
Name: plotHorizontalLine
Purpose: draws a horizontal line to the screen of a specified width,
		 with the left end at the specified coordinate
Input:	base 	- Pointer to the start of the frame buffer, type UINT8*
		x    	- x part of the coordinate, type int
		y	 	- y part of the coordinate, type int
		width	- width of the line, type int
*/
void plotHorizontalLine(UINT8* base, int x, int y, int width)
{
	const UINT8 fillMask = 0xff;
	int x2 = x + width - 1;
	UINT8* row = base + (y * BYTES_PER_ROW);
	UINT8* currentByte = row + (x >> 3);
	UINT8* lastByte;
	
	if( x >= 0 && x < SCREEN_WIDTH &&
		y >= 0 && y < SCREEN_HEIGHT )
	{
		if( x2 >= SCREEN_WIDTH)
		{
			x2 = SCREEN_WIDTH - 1;
			width = x2 - x + 1;
		}
		
		lastByte = row + (x2 >> 3);
		
		if( currentByte == lastByte )
		{
			*currentByte |= (fillMask >> (BYTE_SIZE - width)) << (7 - (x2 & 7));
		}
		else
		{
			*currentByte |= fillMask >> (x & 7);
			currentByte++;
			
			while(currentByte < lastByte)
			{
				*currentByte = fillMask;
				currentByte++;
			}
			
			*currentByte |= fillMask << (7 - (x2 & 7));
			
		}
	}

}


/*
Name: clearHorizontalLine
Purpose: clears a horizontal line on the screen (sets to white) 
		 of a specified width,
		 with the left end at the specified coordinate
Input:	base 	- Pointer to the start of the frame buffer, type UINT8*
		x    	- x part of the coordinate, type int
		y	 	- y part of the coordinate, type int
		width	- width of the line, type int
*/
void clearHorizontalLine(UINT8* base, int x, int y, int width)
{
	const UINT8 fillMask = 0xff;
	const UINT8 clearMask = 0x00;
	int x2 = x + width - 1;
	UINT8* row = base + (y * BYTES_PER_ROW);
	UINT8* currentByte = row + (x >> 3);
	UINT8* lastByte;
	
	
	if( x >= 0 && x < SCREEN_WIDTH &&
		y >= 0 && y < SCREEN_HEIGHT )
	{
		if( x2 >= SCREEN_WIDTH)
		{
			x2 = SCREEN_WIDTH - 1;
			width = x2 - x + 1;
		}
		
		lastByte = row + (x2 >> 3);
		
		if( currentByte == lastByte )
		{
			*currentByte &= ~((fillMask >> (BYTE_SIZE - width)) << (7 - (x2 & 7)));
		}
		else
		{
			*currentByte &= ~(fillMask >> (x & 7));
			currentByte++;
			
			while(currentByte < lastByte)
			{
				*currentByte = clearMask;
				currentByte++;
			}
			
			*currentByte &= ~(fillMask << (7 - (x2 & 7)));
			
		}
	}
}


/*
Name: xorHorizontalLine
Purpose: xors a horizontal line to the screen of a specified width,
		 with the left end at the specified coordinate
Input:	base 	- Pointer to the start of the frame buffer, type UINT8*
		x    	- x part of the coordinate, type int
		y	 	- y part of the coordinate, type int
		width	- width of the line, type int
*/
void xorHorizontalLine(UINT8* base, int x, int y, int width)
{
	const UINT8 fillMask = 0xff;
	int x2 = x + width - 1;
	UINT8* row = base + (y * BYTES_PER_ROW);
	UINT8* currentByte = row + (x >> 3);
	UINT8* lastByte;
	
	if( x >= 0 && x < SCREEN_WIDTH &&
		y >= 0 && y < SCREEN_HEIGHT )
	{
		if( x2 >= SCREEN_WIDTH)
		{
			x2 = SCREEN_WIDTH - 1;
			width = x2 - x + 1;
		}
		
		lastByte = row + (x2 >> 3);
		
		if( currentByte == lastByte )
		{
			*currentByte ^= (fillMask >> (BYTE_SIZE - width)) << (7 - (x2 & 7));
		}
		else
		{
			*currentByte ^= fillMask >> (x & 7);
			currentByte++;
			
			while(currentByte < lastByte)
			{
				*currentByte = fillMask;
				currentByte++;
			}
			
			*currentByte ^= fillMask << (7 - (x2 & 7));
			
		}
	}

}


/*
Name: plotDiagonalLine
Purpose: draws a diagonal line to the screen
Input:	base 	- Pointer to the start of the frame buffer, type UINT8*
		x1    	- First x coordinate of the line, type int
		y1	 	- First y coordinate of the line, type int
		x2		- Second x coordinate of the line, type int
		y2		- Second y coordinate of the line, type int
*/
void plotDiagonalLine(UINT8* base, int x1, int y1, int x2, int y2)
{
    /*
	double deltaX = abs(x2 - x1);
	double deltaY = abs(y2 - y1);
    */
    double deltaX = x2 - x1;
	double deltaY = y2 - y1;
	double slope;
	double currentError;
	int yPlot = y1;
	int xPlot = x1;
	int start;
	int end;
	int incrementDiagonal;
	
	if(deltaX > deltaY)
	{
		slope = deltaY / deltaX;
	}
	else
	{
		slope = deltaX / deltaY;
	}
	
	currentError = slope - 0.5;
	
	if(deltaX > deltaY)
	{
		slope = deltaY / deltaX;
		currentError = slope - 0.5;		
		if(x1 < x2)
		{
			start = x1;
			end = x2;
		}
		else
		{
			start = x2;
			end = x1;
		}
		if(y1 < y2)
		{
			incrementDiagonal = 1;
		}
		else
		{
			incrementDiagonal = -1;
		}
		while(start < end)
		{	
			plotPixel(base, start, yPlot);
			currentError = currentError + slope;
			if(currentError >= 0.5)
			{
				yPlot = yPlot + incrementDiagonal;
				currentError = currentError - 1;
			}
			start++;
		}
	}
	else 
	{
		if(y1 < y2)
		{
			start = y1;
			end = y2;
		}
		else
		{
			start = y2;
			end = y1;
		}
		if(x1 < x2)
		{
			incrementDiagonal = 1;
		}
		else
		{
			incrementDiagonal = -1;
		}
		while(start < end)
		{	
			plotPixel(base, xPlot, start);
			currentError = currentError + slope;
			if(currentError >= 0.5)
			{
				xPlot = xPlot + incrementDiagonal;
				currentError = currentError - 1;
			}
			start++;
		}
	}
}
/*
Name: plotLine
Purpose: draws a circle to the screen
Input:	base 	- Pointer to the start of the frame buffer, type UINT8*
		x0		- x coordinate of the center of the circle, type int
		y0		- y coordinate of the center of the circle, type int
		radius	- radius of the circle
*/
void plotLine(UINT8* base, int x1, int y1, int x2, int y2)
{
	if(y1 == y2)
	{
		if(x1 <= x2)
		{
			plotHorizontalLine(base, x1, y1, (x2 - x1) + 1);
		}
		else
		{
			plotHorizontalLine(base, x2, y1, (x1 - x2) + 1);
		}
	}
	else if(x1 == x2)
	{
		if(y1 <= y2)
		{
			plotVerticalLine(base, x1, y1, (y2 - y1) + 1);
		}
		else
		{
			plotVerticalLine(base, x1, y2, (y1 - y2) + 1);
		}
	}
	else
	{
		plotDiagonalLine(base, x1, y1, x2, y2);
	}
}


/*
Name: fillRectangle
Purpose: draws a solid rectangle to the screen of a specified width and height,
		 with the top left corner at the specified coordinate
Input:	base 	- Pointer to the start of the frame buffer, type UINT8*
		x    	- x part of the coordinate, type int
		y	 	- y part of the coordinate, type int
		width	- height of the line, type int
		height	- height of the line, type int
*/
void fillRectangle(UINT8* base, int x, int y, int width, int height)
{
	int rowCount;
	
	if( x >= 0 && x < SCREEN_WIDTH &&
		y >= 0 && y < SCREEN_HEIGHT )
	{
		for(rowCount = 0; rowCount < height && y < SCREEN_HEIGHT; rowCount++)
		{
			plotHorizontalLine(base, x, y, width);
			y++;
		}
	}
}


/*
Name: plotRectangle
Purpose: draws a hollow rectangle to the screen of a specified width and height,
		 with the top left corner at the specified coordinate
Input:	base 	- Pointer to the start of the frame buffer, type UINT8*
		x    	- x part of the coordinate, type int
		y	 	- y part of the coordinate, type int
		width	- height of the line, type int
		height	- height of the line, type int
*/
void plotRectangle(UINT8* base, int x, int y, int width, int height)
{
	int x2 = x + width - 1;
	int y2 = y + height - 1;
	
	if( x >= 0 && x < SCREEN_WIDTH &&
		y >= 0 && y < SCREEN_HEIGHT )
	{
		plotHorizontalLine(base, x, y, width);
		plotHorizontalLine(base, x, y2, width);
		plotVerticalLine(base, x, y, height);
		plotVerticalLine(base, x2, y, height);
	}
}


/*
Name: clearRectangle
Purpose: clears a solid rectangle from the screen of a specified width and height,
		 with the top left corner at the specified coordinate
Input:	base 	- Pointer to the start of the frame buffer, type UINT8*
		x    	- x part of the coordinate, type int
		y	 	- y part of the coordinate, type int
		width	- height of the line, type int
		height	- height of the line, type int
*/
void clearRectangle(UINT8* base, int x, int y, int width, int height)
{
	int rowCount;
	
	if( x >= 0 && x < SCREEN_WIDTH &&
		y >= 0 && y < SCREEN_HEIGHT )
	{
		for(rowCount = 0; rowCount < height && y < SCREEN_HEIGHT; rowCount++)
		{
			clearHorizontalLine(base, x, y, width);
			y++;
		}
	}
}


/*
Name: plotBitmap8
Purpose: draws a one byte wide (8 px) bitmap of specified height to the screen
Input:	base 	- Pointer to the start of the frame buffer, type UINT8*
		x    	- x part of the coordinate, type int
		y	 	- y part of the coordinate, type int
		bitmap[]- array containing the bitmap data, type UINT8 
		height	- height of the line, type int
*/
void plotBitmap8(UINT8* base, int x, int y, const UINT8 bitmap[], int height)
{
	register UINT8* currentByte = (base + (y * BYTES_PER_ROW) + (x >> 3));
	register UINT8 currentByteShift = (x & 7);
	register UINT8 nextByteShift = (BYTE_SIZE - (x & 7));
	register int index;
	int x2 = x + BYTE_SIZE - 1;
	
	if( x < 0)
	{
		currentByte = (base + ((y - 1) * BYTES_PER_ROW) + ((SCREEN_WIDTH + x) >> 3));
		currentByteShift = ((SCREEN_WIDTH + x) & 7);
		nextByteShift = (BYTE_SIZE - ((SCREEN_WIDTH + x) & 7));
	}
	
	if( x2 >= 0 && x < SCREEN_WIDTH &&
		y >= 0 && y < SCREEN_HEIGHT )
	{
		for(index = 0; index < height && y < SCREEN_HEIGHT; index++)
		{
			if( x >= 0)
			{
				*currentByte |=  bitmap[index] >> currentByteShift;
			}
			if((x2 + 1) < SCREEN_WIDTH)
			{
				*(currentByte + 1) |= bitmap[index] << nextByteShift;
			}
			y++;
			currentByte += BYTES_PER_ROW;
		}
	}
}


/*
Name: plotBitmap16
Purpose: draws a one word wide (16 px) bitmap of specified height to the screen
Input:	base 	- Pointer to the start of the frame buffer, type UINT16*
		x    	- x part of the coordinate, type int
		y	 	- y part of the coordinate, type int
		bitmap[]- array containing the bitmap data, type UINT16 
		height	- height of the line, type int
*/
void plotBitmap16(UINT16* base, int x, int y, const UINT16 bitmap[], int height)
{
	register UINT16* currentWord = (base + (y * WORDS_PER_ROW) + (x >> 4));
	register UINT16 currentWordShift = (x & 15);
	register UINT16 nextWordShift = (WORD_SIZE - (x & 15));
	register int index;
	int x2 = x + WORD_SIZE - 1;
	
	if( x < 0)
	{
		currentWord = (base + ((y - 1) * WORDS_PER_ROW) + ((SCREEN_WIDTH + x + 1) >> 4));
		currentWordShift = ((SCREEN_WIDTH + x) & 15);
		nextWordShift = (WORD_SIZE - ((SCREEN_WIDTH + x) & 15));
	}
	
	if( x2 >= 0 && x < SCREEN_WIDTH &&
		y >= 0 && y < SCREEN_HEIGHT )
	{
		for(index = 0; index < height && y < SCREEN_HEIGHT; index++)
		{
			if( x >= 0)
			{
				*currentWord |=  bitmap[index] >> currentWordShift;
			}
			if((x2 + 1) < SCREEN_WIDTH)
			{
				*(currentWord + 1) |= bitmap[index] << nextWordShift;
			}
			y++;
			currentWord += WORDS_PER_ROW;
		}
	}
}


/*
Name: plotBitmap32
Purpose: draws a one long wide (32 px) bitmap of specified height to the screen
Input:	base 	- Pointer to the start of the frame buffer, type UINT32*
		x    	- x part of the coordinate, type int
		y	 	- y part of the coordinate, type int
		bitmap[]- array containing the bitmap data, type UINT32 
		height	- height of the line, type int
*/
void plotBitmap32(UINT32* base, int x, int y, const UINT32 bitmap[], int height)
{
	register UINT32* currentLong = (base + (y * LONGS_PER_ROW) + (x >> 5));
	register UINT32 currentLongShift = (x & 31);
	register UINT32 nextLongShift = (LONG_SIZE - currentLongShift);
	register int index;
	int x2 = x + LONG_SIZE - 1;
	
	if( x < 0 )
	{
		currentLong = (base + ((y - 1) * LONGS_PER_ROW) + ((SCREEN_WIDTH + x) >> 5));
		currentLongShift = ((SCREEN_WIDTH + x) & 31);
		nextLongShift = (LONG_SIZE - currentLongShift);
	}
	
	if( x2 >= 0 && x < SCREEN_WIDTH &&
		y >= 0 && y < SCREEN_HEIGHT )
	{
		for(index = 0; index < height && y < SCREEN_HEIGHT; index++)
		{
			if( x >= 0)
			{
				*currentLong |=  bitmap[index] >> currentLongShift;
			}
			if((x2 + 1) < SCREEN_WIDTH)
			{
				*(currentLong + 1) |= bitmap[index] << nextLongShift;
			}
			y++;
			currentLong += LONGS_PER_ROW;
		}
	}
}


/*
Name: plotBitmap64
Purpose: draws a 2 long wide (64 px) bitmap of specified height to the screen
Input:	base 	- Pointer to the start of the frame buffer, type UINT32*
		x    	- x part of the coordinate, type int
		y	 	- y part of the coordinate, type int
		bitmap[]- array containing the bitmap data, type UINT32 
		height	- height of the line, type int
Details: Intended for Deputy Arsh sprites
*/
void plotBitmap64(UINT32* base, int x, int y, const UINT32 bitmap[], int height)
{
	const int LONGS_PER_BITMAP_ROW = 2;
	register UINT32* currentLong = (base + (y * LONGS_PER_ROW) + (x >> 5));
	register UINT32 currentLongShift = (x & 31);
	register UINT32 nextLongShift = (LONG_SIZE - currentLongShift);
	int rowCount;
	int index = 0;
	int longIndex;
	int x2 = x + LONG_SIZE - 1;
	UINT8 offEdge = FALSE;
	int xInitial = x;
	
	if( x < 0 )
	{
		currentLong = (base + ((y - 1) * LONGS_PER_ROW) + ((SCREEN_WIDTH + x) >> 5));
		currentLongShift = ((SCREEN_WIDTH + x) & 31);
		nextLongShift = (LONG_SIZE - currentLongShift);
	}
	
	if( x + 64 - 1 >= 0 && x < SCREEN_WIDTH &&
		y >= 0 && y < SCREEN_HEIGHT )
	{
		for(rowCount = 0; rowCount < height && y < SCREEN_HEIGHT; rowCount++)
		{	
			for(longIndex = 0; !offEdge && (longIndex < LONGS_PER_BITMAP_ROW); longIndex++)
			{
				if( x >= 0)
				{
					*(currentLong + longIndex) |=  bitmap[index] >> currentLongShift;
					if((x2 + 1) < SCREEN_WIDTH)
					{
						*(currentLong + longIndex + 1) |= bitmap[index] << nextLongShift;
					}
					else
					{
						offEdge = TRUE;
						index += LONGS_PER_BITMAP_ROW - longIndex - 1;
					}
				}
				else if( x2 >= 0)
				{
					*(currentLong + longIndex + 1) |= bitmap[index] << nextLongShift;
				}
				x += LONG_SIZE;
				x2 += LONG_SIZE;
				index++;
			}
			y++;
			currentLong += LONGS_PER_ROW;
			x = xInitial;
			offEdge = FALSE;
			x2 = x + LONG_SIZE - 1;
		}
	}
}


/*
Name: xorBitmap64
Purpose: draws a 2 long wide (64 px) bitmap of specified height to the screen
Input:	base 	- Pointer to the start of the frame buffer, type UINT32*
		x    	- x part of the coordinate, type int
		y	 	- y part of the coordinate, type int
		bitmap[]- array containing the bitmap data, type UINT32 
		height	- height of the line, type int
Details: Intended for Deputy Arsh sprites
*/
void xorBitmap64(UINT32* base, int x, int y, const UINT32 bitmap[], int height)
{
	const int LONGS_PER_BITMAP_ROW = 2;
	register UINT32* currentLong = (base + (y * LONGS_PER_ROW) + (x >> 5));
	register UINT32 currentLongShift = (x & 31);
	register UINT32 nextLongShift = (LONG_SIZE - currentLongShift);
	int rowCount;
	int index = 0;
	int longIndex;
	int x2 = x + LONG_SIZE - 1;
	UINT8 offEdge = FALSE;
	int xInitial = x;
	
	if( x < 0 )
	{
		currentLong = (base + ((y - 1) * LONGS_PER_ROW) + ((SCREEN_WIDTH + x) >> 5));
		currentLongShift = ((SCREEN_WIDTH + x) & 31);
		nextLongShift = (LONG_SIZE - currentLongShift);
	}
	
	if( x + 64 - 1 >= 0 && x < SCREEN_WIDTH &&
		y >= 0 && y < SCREEN_HEIGHT )
	{
		for(rowCount = 0; rowCount < height && y < SCREEN_HEIGHT; rowCount++)
		{	
			for(longIndex = 0; !offEdge && (longIndex < LONGS_PER_BITMAP_ROW); longIndex++)
			{
				if( x >= 0)
				{
					*(currentLong + longIndex) ^=  bitmap[index] >> currentLongShift;
					if((x2 + 1) < SCREEN_WIDTH)
					{
						*(currentLong + longIndex + 1) ^= bitmap[index] << nextLongShift;
					}
					else
					{
						offEdge = TRUE;
						index += LONGS_PER_BITMAP_ROW - longIndex - 1;
					}
				}
				else if( x2 >= 0)
				{
					*(currentLong + longIndex + 1) ^= bitmap[index] << nextLongShift;
				}
				x += LONG_SIZE;
				x2 += LONG_SIZE;
				index++;
			}
			y++;
			currentLong += LONGS_PER_ROW;
			x = xInitial;
			offEdge = FALSE;
			x2 = x + LONG_SIZE - 1;
		}
	}
}


/*
Name: plotBitmap80
Purpose: draws a 5 word wide (80 px) bitmap of specified height to the screen
Input:	base 	- Pointer to the start of the frame buffer, type UINT16*
		x    	- x part of the coordinate, type int
		y	 	- y part of the coordinate, type int
		bitmap[]- array containing the bitmap data, type UINT16 
		height	- height of the line, type int
Details: Intended for obstacle sprites
*/
void plotBitmap80(UINT16* base, int x, int y, const UINT16 bitmap[], int height)
{
	const int WORDS_PER_BITMAP_ROW = 5;
	register UINT16* currentWord = (base + (y * WORDS_PER_ROW) + (x >> 4));
	register UINT16 currentWordShift = (x & 15);
	register UINT16 nextWordShift = (WORD_SIZE - currentWordShift);
	int rowCount;
	int index = 0;
	int wordIndex;
	int x2 = x + WORD_SIZE - 1;
	UINT8 offEdge = FALSE;
	int xInitial = x;
	
	if( x < 0 )
	{
		currentWord = (base + ((y - 1) * WORDS_PER_ROW) + ((SCREEN_WIDTH + x + 1) >> 4));
		currentWordShift = ((SCREEN_WIDTH + x) & 15);
		nextWordShift = (WORD_SIZE - currentWordShift);
	}
	
	if( x + 80 - 1 >= 0 && x < SCREEN_WIDTH &&
		y >= 0 && y < SCREEN_HEIGHT )
	{
		for(rowCount = 0; rowCount < height && y < SCREEN_HEIGHT; rowCount++)
		{	
			for(wordIndex = 0; !offEdge && (wordIndex < WORDS_PER_BITMAP_ROW); wordIndex++)
			{
				if( x >= 0)
				{
					*(currentWord + wordIndex) |=  bitmap[index] >> currentWordShift;
					if((x2 + 1) < SCREEN_WIDTH)
					{
						*(currentWord + wordIndex + 1) |= bitmap[index] << nextWordShift;
					}
					else
					{
						offEdge = TRUE;
						index += WORDS_PER_BITMAP_ROW - wordIndex - 1;
					}
				}
				else if( x2 >= 0)
				{
					*(currentWord + wordIndex + 1) |= bitmap[index] << nextWordShift;
				}
				x += WORD_SIZE;
				x2 += WORD_SIZE;
				index++;
			}
			y++;
			currentWord += WORDS_PER_ROW;
			x = xInitial;
			offEdge = FALSE;
			x2 = x + WORD_SIZE - 1;
		}
	}
}


/*
Name: plotBitmap96
Purpose: draws a 2 long wide (96 px) bitmap of specified height to the screen
Input:	base 	- Pointer to the start of the frame buffer, type UINT32*
		x    	- x part of the coordinate, type int
		y	 	- y part of the coordinate, type int
		bitmap[]- array containing the bitmap data, type UINT32 
		height	- height of the line, type int
Details: Intended for Deputy Arsh slide sprite
*/
void plotBitmap96(UINT32* base, int x, int y, const UINT32 bitmap[], int height)
{
	const int LONGS_PER_BITMAP_ROW = 3;
	register UINT32* currentLong = (base + (y * LONGS_PER_ROW) + (x >> 5));
	register UINT32 currentLongShift = (x & 31);
	register UINT32 nextLongShift = (LONG_SIZE - currentLongShift);
	int rowCount;
	int index = 0;
	int longIndex;
	int x2 = x + LONG_SIZE - 1;
	UINT8 offEdge = FALSE;
	int xInitial = x;
	
	if( x < 0 )
	{
		currentLong = (base + ((y - 1) * LONGS_PER_ROW) + ((SCREEN_WIDTH + x) >> 5));
		currentLongShift = ((SCREEN_WIDTH + x) & 31);
		nextLongShift = (LONG_SIZE - currentLongShift);
	}
	
	if( x + 96 - 1 >= 0 && x < SCREEN_WIDTH &&
		y >= 0 && y < SCREEN_HEIGHT )
	{
		for(rowCount = 0; rowCount < height && y < SCREEN_HEIGHT; rowCount++)
		{	
			for(longIndex = 0; !offEdge && (longIndex < LONGS_PER_BITMAP_ROW); longIndex++)
			{
				if( x >= 0)
				{
					*(currentLong + longIndex) |=  bitmap[index] >> currentLongShift;
					if((x2 + 1) < SCREEN_WIDTH)
					{
						*(currentLong + longIndex + 1) |= bitmap[index] << nextLongShift;
					}
					else
					{
						offEdge = TRUE;
						index += LONGS_PER_BITMAP_ROW - longIndex - 1;
					}
				}
				else if( x2 >= 0)
				{
					*(currentLong + longIndex + 1) |= bitmap[index] << nextLongShift;
				}
				x += LONG_SIZE;
				x2 += LONG_SIZE;
				index++;
			}
			y++;
			currentLong += LONGS_PER_ROW;
			x = xInitial;
			offEdge = FALSE;
			x2 = x + LONG_SIZE - 1;
		}
	}
}


/*
Name: plotBitmapFullscreen
Purpose: draws a bitmap the size of the entire screen to the screen
Input:	base 	- Pointer to the start of the frame buffer, type UINT32*
		bitmap[]- array containing the bitmap data, type UINT32 
Details: screen is 640x400
         intended for main menu sprite
*/
void plotBitmapFullscreen(UINT32* base, const UINT32 bitmap[])
{
    int index;
    
    for( index = 0; index < LONGS_ON_SCREEN; index++)
    {
        *(base++) |= bitmap[index];
    }
}


/*
Name: plotCircle
Purpose: draws a circle to the screen
Input:	base 	- Pointer to the start of the frame buffer, type UINT8*
		x0		- x coordinate of the center of the circle, type int
		y0		- y coordinate of the center of the circle, type int
		radius	- radius of the circle
*/
void plotCircle(UINT8* base, int x0, int y0, int radius)
{
	int x = 0;
	int y = radius;
	int decision = 3 - (2 * radius);
	
	while(y >= x)
	{
		plotPixel(base, x0 + x, y0 + y);
		plotPixel(base, x0 + y, y0 + x);
		plotPixel(base, x0 - y, y0 + x);
		plotPixel(base, x0 - x, y0 + y);
		plotPixel(base, x0 - x, y0 - y);
		plotPixel(base, x0 - y, y0 - x);
		plotPixel(base, x0 + y, y0 - x);
		plotPixel(base, x0 + x, y0 - y);
		
		if(decision < 0)
		{
			decision = decision + (4 * x) + 6;
		}
		else
		{
			y--;
			decision = decision + (4 * (x - y)) + 10; 
		}
		x++;
	}
}


/*
Name: plotChar8
Purpose: writes the specified character to the screen, 8x8 px
Input: 	base 		- Pointer to the start of the frame buffer, type UINT8*
		x    		- x part of the coordinate, type int
		y	 		- y part of the coordinate, type int
		fontmap[]	- array containing the font table data, type UINT8 
		character	- the character being written to the screen, type char
*/
void plotChar8(UINT8* base, int x, int y, const UINT8 fontmap[], char character)
{
	
	register UINT8* currentByte = (base + (y * BYTES_PER_ROW) + (x >> 3));
	register UINT8 currentByteShift = (x & 7);
	register UINT8 nextByteShift = (BYTE_SIZE - (x & 7));
	register int index;
	register UINT8 charStart = (((character) - ' ') << 3);
	int x2 = x + BYTE_SIZE - 1;
	
	if( x < 0)
	{
		currentByte = (base + ((y - 1) * BYTES_PER_ROW) + ((SCREEN_WIDTH + x) >> 3));
		currentByteShift = ((SCREEN_WIDTH + x) & 7);
		nextByteShift = (BYTE_SIZE - ((SCREEN_WIDTH + x) & 7));
	}
	
	if( x2 >= 0 && x < SCREEN_WIDTH &&
		y >= 0 && y < SCREEN_HEIGHT )
	{
		for(index = 0; index < FONT_HEIGHT && y < SCREEN_HEIGHT; index++)
		{
			if( x >= 0)
			{
				*currentByte |=  font[charStart + index] >> currentByteShift;
			}
			if((x2 + 1) < SCREEN_WIDTH)
			{
				*(currentByte + 1) |= font[charStart + index] << nextByteShift;
			}
			y++;
			currentByte += BYTES_PER_ROW;
		}
	}
}


/*
Name: plotDigit8
Purpose: writes the specified character to the screen, 8x12 px
Input: 	base 		- Pointer to the start of the frame buffer, type UINT8*
		x    		- x part of the coordinate, type int
		y	 		- y part of the coordinate, type int
		digitmap[]	- array containing the digit font data, type UINT8 
		character	- the character being written to the screen, type char
*/
void plotDigit8(UINT8* base, int x, int y, const UINT8 digitmap[], int digit)
{
	
	register UINT8* currentByte = (base + (y * BYTES_PER_ROW) + (x >> 3));
	register UINT8 currentByteShift = (x & 7);
	register UINT8 nextByteShift = (BYTE_SIZE - (x & 7));
	register int index;
	register UINT8 charStart = (digit * DIGIT_HEIGHT);
	int x2 = x + BYTE_SIZE - 1;
	
	if( x < 0)
	{
		currentByte = (base + ((y - 1) * BYTES_PER_ROW) + ((SCREEN_WIDTH + x) >> 3));
		currentByteShift = ((SCREEN_WIDTH + x) & 7);
		nextByteShift = (BYTE_SIZE - ((SCREEN_WIDTH + x) & 7));
	}
	
	if( digit <= 9 && digit >= 0)
	{
		if( x2 >= 0 && x < SCREEN_WIDTH &&
			y >= 0 && y < SCREEN_HEIGHT )
		{
			for(index = 0; index < DIGIT_HEIGHT && y < SCREEN_HEIGHT; index++)
			{
				if( x >= 0)
				{
					*currentByte |=  digitmap[charStart + index] >> currentByteShift;
				}
				if((x2 + 1) < SCREEN_WIDTH)
				{
					*(currentByte + 1) |= digitmap[charStart + index] << nextByteShift;
				}
				y++;
				currentByte += BYTES_PER_ROW;
			}
		}
	}
}
















