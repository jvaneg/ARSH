/*
Name: 	Joel v
		Kieran K
		
Module: Raster

Purpose: Contains all of the functions related to drawing basic shapes, lines,
		 and bitmaps of various sizes to the screen.

Details: Assumes the screen is monochromatic, and 640x400 pixels in size.
*/

#ifndef RASTER_H
#define RASTER_H

#include "types.h"
#include "font.h"
#include <math.h>

/* Useful constants for the raster module */
#define SCREEN_HEIGHT 400
#define SCREEN_WIDTH 640

#define LONGS_ON_SCREEN 8000
#define BYTES_PER_ROW 80
#define WORDS_PER_ROW 40
#define LONGS_PER_ROW 20
#define BYTE_SIZE 8
#define WORD_SIZE 16
#define LONG_SIZE 32

#define TRUE 1
#define FALSE 0


void clearScreen(UINT32* base);
void plotPixel(UINT8* base, int x, int y);
void plotVerticalLine(UINT8* base, int x, int y, int height);
void plotHorizontalLine(UINT8* base, int x, int y, int width);
void xorHorizontalLine(UINT8* base, int x, int y, int width);
void plotDiagonalLine(UINT8* base, int x1, int y1, int x2, int y2);
void plotLine(UINT8* base, int x1, int y1, int x2, int y2);
void clearHorizontalLine(UINT8* base, int x, int y, int width);
void fillRectangle(UINT8* base, int x, int y, int width, int height);
void plotRectangle(UINT8* base, int x, int y, int width, int height);
void clearRectangle(UINT8* base, int x, int y, int width, int height);
void plotCircle(UINT8* base, int x, int y, int radius);

void plotChar8(UINT8* base, int x, int y, const UINT8 fontmap[], char character);
void plotDigit8(UINT8* base, int x, int y, const UINT8 digitmap[], int digit);
void plotBitmap8(UINT8* base, int x, int y, const UINT8 bitmap[], int height);
void plotBitmap16(UINT16* base, int x, int y, const UINT16 bitmap[], int height);
void plotBitmap32(UINT32* base, int x, int y, const UINT32 bitmap[], int height);
void plotBitmap64(UINT32* base, int x, int y, const UINT32 bitmap[], int height);
void xorBitmap64(UINT32* base, int x, int y, const UINT32 bitmap[], int height);
void plotBitmap80(UINT16* base, int x, int y, const UINT16 bitmap[], int height);
void plotBitmap96(UINT32* base, int x, int y, const UINT32 bitmap[], int height);
void plotBitmapFullscreen(UINT32* base, const UINT32 bitmap[]);


#endif
