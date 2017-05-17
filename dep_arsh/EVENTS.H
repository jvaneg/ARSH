/*
Name:   Joel v
        Kieran K
        
Module: Events

Purpose: Contains all of the functions related to handling events in the main
         game loop.

Details: Event handlers take place in the main game loop after the model has been
         updated in the asynchronous input phase. The event handlers change the game
         world based on the asynchronous model changes.
*/

#ifndef EVENTS_H
#define EVENTS_H

#include "sound_ef.h"
#include "types.h"
#include "model.h"
#include <stdlib.h>
#include <time.h>

/* Constants related to event handler functions */
#define JUMP_RISE_LENGTH 6
#define JUMP_HANG_LENGTH 18
#define JUMP_FALL_LENGTH 6
#define SLIDE_LENGTH 30
#define KICK_LENGTH 30
#define MAX_CLOUD_SPEED 6
#define SCORE_THRESHOLD_1 10
#define SCORE_THRESHOLD_2 35
#define SCORE_THRESHOLD_3 70
#define PHASE_2_VELOCITY 16
#define PHASE_2_SPAWNRATE 55
#define PHASE_3_VELOCITY 22
#define PHASE_3_SPAWNRATE 33
#define PHASE_4_VELOCITY 30
#define PHASE_4_SPAWNRATE 36

/* FUNCTION PROTOTYPES */
void moveObstacle(struct Obstacle* obstacle, struct Score* score, UINT8* spawnRate, UINT8* obstacleVelocity);
void moveCloud(struct Cloud* cloud);
void moveTumbleweed(struct Tumbleweed* weed);
void incrementScore(struct Score* score, UINT8* spawnRate, UINT8* obstacleVelocity);
void checkCollision(struct Arsh* arsh, struct Obstacle* obstacle);
UINT8 checkMouseOver(struct Button* button, int mouseX, int mouseY);

void spawnObstacle(struct Obstacle* obstacle, UINT8 obstacleVelocity);
void spawnObstacleBale(struct Obstacle* obstacle, UINT8 obstacleVelocity);
void spawnObstacleCactus(struct Obstacle* obstacle, UINT8 obstacleVelocity);
void spawnObstacleVulture(struct Obstacle* obstacle, UINT8 obstacleVelocity);
void removeObstacle(struct Obstacle* obstacle);
void resetCloud(struct Cloud* cloud);

void doArshRun(struct Arsh* arsh);
void doArshJump(struct Arsh* arsh);
void doArshSlide(struct Arsh* arsh);
void doArshKick(struct Arsh* arsh);

void doArshJumpRise(struct Arsh* arsh);
void doArshJumpHang(struct Arsh* arsh);
void doArshJumpFall(struct Arsh* arsh);


#endif