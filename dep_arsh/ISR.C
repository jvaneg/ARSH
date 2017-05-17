/*
Name: 	Joel v
		Kieran K
		
Module: isr
*/

#include "isr.h"


/*
Name: installVector

Purpose: replaces a TOS ISR with a custom one

Input: num - the number of the vector being replaced, type int
	   vector - pointer to the function being installed, type Vector
	   
Return value: orig - the original function that was previously installed at this vector, type Vector
*/
Vector installVector(int num, Vector vector)
{
	Vector orig;
	Vector *vectp = (Vector*) ((long) num << 2);
	long oldSsp = Super(0);
	
	orig = *vectp;
	*vectp = vector;
	
	Super(oldSsp);
	return orig;
}


/*
Name: maskInterrupt

Purpose: sets IPL = mask, returns old IPL (interrupt priority level)

Input: mask - the interrupt priority level being set, type int

Return value: oldIpl - the old interrupt priority level, type int

Details: wrapper for setipl that turns on super
*/
int maskInterrupt(int mask)
{
	int oldIpl;
	long oldSsp;
	
	oldSsp = Super(0);
	oldIpl = setipl(mask);
	Super(oldSsp);
	
	return oldIpl;
}