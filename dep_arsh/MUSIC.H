/*
Names: 	Joel v
		Kieran K

Module: Music

Purpose: The music module is responsible for controlling the music in the main game loop.

Details: In the two music structures, any '0' is to be read as silence, any '1' is to be read
	as a sustain of an already playing note, and anything else is the beginning of a new note.
	For example, 119, 1, 1, 0, would read, set tone to 119, sustain, sustain, turn off. Each line
	is separated into a new note (in almost all cases) for readability, and measures of the music are
	noted in inline documentation.
*/
#ifndef SOUND_G
#define SOUND_H

#include "psg.h"
#include "model.h"

#define MUSIC_B_ON_1 127
#define MUSIC_B_ON_2 1023
#define MUSIC_B_ON_3 1791
#define MUSIC_B_OFF_1 1152
#define START_MUSIC_LOOP 383
#define END_MUSIC 1919

extern const UINT32 musicA [];
extern const UINT32 musicB [];

void updateMusic(struct Music* music);


#endif