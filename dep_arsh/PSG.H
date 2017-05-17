/*
Names: 	Joel v
		Kieran K

Module: PSG 

Purpose: The PSG module is used for all of the sub-functions that the sound effect and 
	music module relies on. The module is only responsible for directly interacting with 
	the PSG registers.

Details: If you are not already in supervisor mode, you must enter supervisor mode before
	attempting to make changes to the PSG register.
*/
#ifndef PSG_H
#define PSG_H

#include "types.h"
#include <osbind.h>

#define TRUE 1
#define FALSE 0

#define MAX_5_BIT_VALUE 31
#define MAX_12_BIT_VALUE 4095
#define MAX_16_BIT_VALUE 65535

void write_psg(UINT8 reg, UINT8 val);
void set_tone(UINT8 channel, UINT16 tuning);
void set_volume(UINT8 channel, UINT8 volume);
void initialize_mixer();
void enable_channel(UINT8 channel, UINT8 tone_on, UINT8 noise_on);
void disable_channel(UINT8 channel);
UINT8 read_psg(UINT8 reg);
void set_noise(UINT8 tuning);
void set_envelope(UINT8 shape, UINT16 sustain);
void stop_sound();


#endif