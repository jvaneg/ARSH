#include "sound_ef.h"

const UINT16 jumpEffect [] = 
{
	700, 680, 660, 640, 620, 600, 580, 560,
	540, 520, 500, 480, 462, 444, 426, 408,
	390, 374
};

/*
Name: startJumpEffect

Purpose: begins the jump sound effect
*/
void startJumpEffect()
{
	long oldSsp = Super(0);
	
	resetEffects();
	set_tone(2, jumpEffect[0]);
	enable_channel(2,1,0);
	set_volume(2,0xD);
	
	Super(oldSsp);
	
	return;
}
/*
Name: updateJumpEffect

Purpose: changes the jump sound effect based off of time, 

Input: time - how long has passed since Deputy Arsh has jumped, type UINT8

Details: sound will automatically go to 0 volume, turning it off.
*/
void updateJumpEffect(UINT8 time)
{
	UINT8 updatedVolume;
	
	set_tone(2, jumpEffect[time]);
	
	if(time > 4)
	{
		updatedVolume = 17 - time; /* starts decrementing volume at for last tones */
		set_volume(2, updatedVolume);
	}
	
	return;
}
/*
Name: playSlideEffect

Purpose: plays the slide effect when Deputy Arsh slides

Details: due to the envelope shape selected, volume automatically turns off
*/
void playSlideEffect()
{
	long oldSsp = Super(0);
	
	resetEffects();
	set_tone(2, 3895);
	set_noise(31);
	enable_channel(2,1,1);
	set_volume(2, 16);
	set_envelope(0, 3500);
	
	Super(oldSsp);
	
	return;
}
/*
Name: playKickEffect

Purpose: plays the kcik effect when Deputy Arsh kicks a cactus

Details: due to the envelope shape selected, volume automatically turns off
*/
void playKickEffect()
{
	resetEffects();
	set_tone(2, 2750); 
	set_noise(20);
	enable_channel(2,1,1);
	set_volume(2, 16);
	set_envelope(0, 1200);
	
	return;
}
/*
Name: resetEffects

Purpose: resets the sound effect channel to prep for a new effect
*/
void resetEffects()
{
	disable_channel(2);
	return;
}