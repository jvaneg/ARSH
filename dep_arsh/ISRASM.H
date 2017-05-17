/*
Name:   Joel v
        Kieran K
        
Module: inputasm

Purpose: Contains the assembly functions used by the isr module
*/

#ifndef ISRASM_H
#define ISRASM_H

void vblisr();
void ikbdisr();
int setipl(int mask); /* must be called from supervisor mode */

#endif