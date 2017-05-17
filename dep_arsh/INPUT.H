/*
Name:   Joel v
        Kieran K
        
Module: Input

Purpose: Contains the functions related to reading from the ikbd buffer,
         and reading/writing from/to the video base register
*/

#ifndef INPUT_H
#define INPUT_H

#include "types.h"
#include "inputasm.h"
#include "ikbd.h"
#include "isr.h"
#include <osbind.h>


UINT8 inputPending(void);
UINT8 readChar(void);
UINT8 readKeyMap(void);
UINT32 getTime(void);
UINT32* getVideoBase(void);
void setVideoBase(UINT32* newVideoBase);




#endif