#include "psg.h"
/*
Name: write_psg

Purpose: puts a value into the designated PSG register

Input: reg - the register that we are editting, type UINT8
	   val - the 8 bit value that we are putting into the register, type UINT8

Details: We do not go into supervisor mode for this, as this causes the game to
	break when the game enters the VBL_ISR. If we are not in the ISR, supervisor
	mode should be entered before using this function.
*/
void write_psg(UINT8 reg, UINT8 val)
{
	volatile char *PSG_reg_select = 0xFF8800;
	volatile char *PSG_reg_write  = 0xFF8802;
	
	*PSG_reg_select = reg;
	*PSG_reg_write  = val;
	
	return;
}

/*
Name: set_tone

Purpose: changes the tuning of a designated sound channel

Input: channel - the channel we are changing, type UINT8
	   tuning - the 16 bit number we are putting in the coarse and fine registers, type UINT16

Details: Channel 0 = A, 1 = B, 2 = C. Tuning is maximum a 12 bit value.
*/
void set_tone(UINT8 channel, UINT16 tuning)
{
	UINT8 fineChannel = channel * 2;
	UINT8 coarseChannel = fineChannel + 1;
	UINT8 fine;
	UINT8 coarse;
	
	if((tuning >= 0 && tuning <= MAX_12_BIT_VALUE) &&
	    (channel == 0 || channel == 1 || channel == 2))
	{
		fine = tuning & 0x0FF;
		coarse = (tuning & 0xF00) >> 8;
		
		write_psg(fineChannel, fine);
		write_psg(coarseChannel, coarse);
	}
	
	return;
}
/* channel - 0=A, 1=B, 2=C 
   volume  - 5 bits - If 5th bit is set, then the volume is determined
					  by the lower 5 envelope generator bits, otherwise
					  it is determined by the lower four bits
					  USE 15 OR LESS FOR TONE VOLUME (not envelope)
					  setting volume to 1 is equivilant to setting to 0
   MAX VOLUME LEVEL is 31 (max 5 bits value) */
/*
Name: set_volume

Purpose: changes the volume of a designated channel

Input: channel - the channel we are changing, type UINT8
	   volume - the 8 bit number we are using for the volume, type UINT8

Details: Channel 0 = A, 1 = B, 2 = C. Volume is maximum a 5 bit value.
	If the 5th bit is set, then the volume is dependant upon the envelope
	generator.
*/
void set_volume(UINT8 channel, UINT8 volume)
{
	UINT8 volumeChannel = channel + 8;
	
	if((volume >= 0 && volume <= MAX_5_BIT_VALUE) &&
	    (channel == 0 || channel == 1 || channel == 2))
	{
		write_psg(volumeChannel, volume);
	}
	
	return;
}
/*
Name: initialize_mixer

Purpose: preps the channel mixer for the beginning of the game

*/
void initialize_mixer()
{
    UINT8 cleanMixer = 0xFC; /* TURN ON MUSIC CHANNELS */
	long oldSsp = Super(0);
    
    write_psg(7, cleanMixer);
	
	Super(oldSsp);

    return;
}   
/*
Name: enable_channel

Purpose: enables a channel's tone, noise or both

Input: channel - the channel we are changing, type UINT8
	   tone_on - if we wish to turn on the channels tone, type UINT8
	   noise_on - if we wish to turn on the channels noise, type UINT8

Details: Channel 0 = A, 1 = B, 2 = C. 
*/
void enable_channel(UINT8 channel, UINT8 tone_on, UINT8 noise_on)
{	
	UINT8 mixerControl;
    mixerControl = read_psg(7); /* get current reg value */
    
    
	if((tone_on == TRUE || tone_on == FALSE) && /* sorry paul this is for making sure its in bounds */
		(noise_on == TRUE || noise_on == FALSE))
	{
		switch(channel)
		{
			case 0 :
				if(tone_on)
				{
					mixerControl = mixerControl & 0xFE;
				}
				if(noise_on)
				{
					mixerControl = mixerControl & 0xF7;
				}
				write_psg(7, mixerControl);
				break;
			case 1 :
				if(tone_on)
				{
					mixerControl = mixerControl & 0xFD;
				}
				if(noise_on)
				{
					mixerControl = mixerControl & 0xEF;
				}
				write_psg(7, mixerControl);
				break;
			case 2 :
				if(tone_on)
				{
					mixerControl = mixerControl & 0xFB;
				}
				if(noise_on)
				{
					mixerControl = mixerControl & 0xDF;
				}
				write_psg(7, mixerControl);
				break;
			default :
				;
		}
	}	
	return;
}
/*
Name: read_psg

Purpose: reads the value in the psg's resgister

Input: reg - the register that we wish to read, type UINT8

Output: psgValue - the value in the register that we are reading, type UINT8 
*/
UINT8 read_psg(UINT8 reg)
{
	volatile char *PSG_reg_select = 0xFF8800;
	UINT8 psgValue;
	
    *PSG_reg_select = reg;
	psgValue = *PSG_reg_select;
	
	return psgValue;
}
/*
Name: set_noise

Purpose: changes the noise of all channels

Input: tuning - the value that we wish to use for the nosie, type UINT8

Details: max tuning is a 5 bit value. 
*/
void set_noise(UINT8 tuning)
{
	if(tuning >= 0 && tuning <= MAX_5_BIT_VALUE)
	{
		write_psg(6, tuning);
	}
	return;
}

/*
Name: set_envelope

Purpose: changes the sustain and shape of a channel

Input: shape - the shape of envelope we wish to use, type UINT8
	   sustain - the duration of one cycle of the envelope, type UINT16

Details: Will only be used if a channel's volume is 16 or higher.
*/
void set_envelope(UINT8 shape, UINT16 sustain)
{
	UINT8 sustainLSW;
	UINT8 sustainMSW;
	
	if((shape >= 0 && shape <= 15) && 
	   (sustain >= 0 && sustain <= MAX_16_BIT_VALUE))
	   {
		   sustainLSW = sustain & 0xFF;
		   sustainMSW = (sustain & 0xFF00) >> 8;
		   write_psg(11, sustainLSW);
		   write_psg(12, sustainMSW);
		   write_psg(13, shape);
	   }
	return;
}
/*
Name: disable_channel

Purpose: disables target channel

Input: channel - the channel we are changing, type UINT8

Details: Channel 0 = A, 1 = B, 2 = C. 
*/
void disable_channel(UINT8 channel)
{
	UINT8 mixerControl;
    mixerControl = read_psg(7);
	
	switch(channel)
	{
		case 0:
			mixerControl = mixerControl | 0x9;
			write_psg(7, mixerControl);
			break;
		case 1:
			mixerControl = mixerControl | 0x12;
			write_psg(7, mixerControl);
			break;
		case 2:
			mixerControl = mixerControl | 0x24;
			write_psg(7, mixerControl);
			break;
		default:
			;
	}
	return;
}
/*
Name: stop_sound

Purpose: turns off all sound
*/
void stop_sound()
{
	long oldSsp = Super(0);
	
	set_volume(0, 0);
	set_volume(1, 0);
	set_volume(2, 0);
	
	Super(oldSsp);
	
	return;
}


