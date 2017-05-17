/*
Name:	Joel v
		Kieran K

Module: Deputy Arsh

Purpose: Contains the main game loop and logic for the exciting
		 western runner hit, Deputy Arsh!

Details:
	Basic structure of the game loop is as follows:
	
		- initialize model
	
		- render first frame
		
		- set quit = false 
		
		- while not quit
			- if input pending
				- process async event
			
			- if render request 
				- render updated model
				
	Input:
		Z - Jump
		X - Kick
		C - Slide
		Q - Quit
		P - (SECRET) Swaps Deputy Arsh with The Bad Bandit
		
	Rules:
		- JUMP over HAYBALES
		- KICK down CACTI
		- SLIDE under VULTURES
		
Assumptions / Limitations / Known bugs:
	
	- 2 Player option generates thousands of images of Paul P instead
	  of launching 2 Player mode (not sure why this happens, we're working on it)
	  
	- Game is not burned onto ROM (no idea how to do this, too hard)
	
	- There are moments where the game (and music) will run slightly too fast,
	  this is because rendering and music is tied to framerate and the framerate
	  is not always constant. This could be fixed by rescaling all timings and
	  decoupling the framerate from the game logic, but it was too late by the time
	  we got to this
*/

#ifndef DEP_ARSH_H
#define DEP_ARSH_H

#include "renderer.h"
#include "events.h"
#include "psg.h"
#include "input.h"
#include "isr.h"
#include "music.h"
#include "ikbd.h"
#include <time.h>
#include <string.h>

#define KEY_UP 0x48
#define KEY_DOWN 0x50
#define KEY_RETURN 0x1C
#define KEY_Q 0x10
#define LMB_CLICK 0xFA
#define LMB_RMB_CLICK 0xFB

#define NO_GAME 0
#define MAIN_MENU 1
#define PLAYING_GAME 2
#define END_SCREEN 3

#define MAIN_1P 0
#define MAIN_2P 1
#define MAIN_QUIT 2

int playGame(void* mainBase, void* altBase);
int playMenu(void* mainBase);
int playEndscreen(void* mainBase, int finalScore);
void procSync(void);

/* Globals required for VBL ISR */
extern UINT8 renderRequest; /* whether or not a render request has been set by the ISR */
extern UINT8 playingGame;   /* whether or not the main game loop is being played */

extern UINT8 globalTimeCounter;   /* the time counter being used in the main game loop */
extern UINT8 oldSpawnRate;      /* the previous obstacle spawnRate to determine if the spawnRate has changed */
extern UINT8 obstacleIndex;     /* index of obstacle array */
extern UINT8 obstacleFound;     /* whether or not an obstacle has been found */

extern struct Model gameWorld; /* the game world */
extern struct MenuModel menu; /* the main menu */
extern struct EndscreenModel endscreen; /* the end screen menu */

#endif