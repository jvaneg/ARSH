/*
Name: 	Joel v
		Kieran K
		
Module: isr

Purpose: contains the functions and typedefs needed to install and operate
	     interrupt service routines
*/

#ifndef ISR_H
#define ISR_H

#include <osbind.h>
#include "israsm.h"

#define VBL_ISR 28

typedef void (*Vector) (); /* a vector is a function start address */

Vector installVector(int num, Vector vector);
int maskInterrupt(int mask);

#endif