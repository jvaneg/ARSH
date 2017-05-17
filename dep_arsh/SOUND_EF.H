/*
Names:  Joel v
        Kieran K

Module: Sound Effects

Purpose: The sound effect module is responsible for controlling creating the awesome sound effects
    that you head while playing Deputy Arsh. 

*/
#ifndef SOUND_EF_H
#define SOUND_EF_H

#include "psg.h"

#include <stdio.h>

extern const UINT16 jumpEffect[];

void startJumpEffect();
void updateJumpEffect(UINT8 time);
void playSlideEffect();
void playKickEffect();
void resetEffects();



#endif