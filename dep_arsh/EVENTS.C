/*
Name: 	Joel v
		Kieran K
		
Module: Events
*/

#include "events.h"

/*
Name: doArshRun

Purpose: performs 1 frame of the arsh run action

Input: arsh - the structure containing all player entity data, type Arsh*

Output: arsh - the structure containing all player entity data, type Arsh*
*/
void doArshRun(struct Arsh* arsh)
{
	arsh->timeInState++;
	 
	if(arsh->timeInState > 100)
	{
		arsh->timeInState = 1;
	}
	return;
}


/*
Name: doArshJump

Purpose: performs 1 frame of the arsh jump action

Input: arsh - the structure containing all player entity data, type Arsh*

Output: arsh - the structure containing all player entity data, type Arsh*
*/
void doArshJump(struct Arsh* arsh)
{
	
	if(arsh->timeInState < JUMP_RISE_LENGTH)
	{
		doArshJumpRise(arsh);	
		arsh->timeInState++;
		updateJumpEffect(arsh->timeInState);
	}
	else if( arsh->timeInState < JUMP_RISE_LENGTH + JUMP_HANG_LENGTH)
	{
		doArshJumpHang(arsh);
		arsh->timeInState++;
		if(arsh->timeInState < 18)
		{
			updateJumpEffect(arsh->timeInState);
		}
	}
	else if( arsh->timeInState < JUMP_RISE_LENGTH + JUMP_HANG_LENGTH + JUMP_FALL_LENGTH)
	{
		doArshJumpFall(arsh);
		arsh->timeInState++;
	}
	else
	{
		setArshRun(arsh);
	}
	
	return;
}


/*
Name: doArshSlide

Purpose: performs 1 frame of the arsh slide action

Input: arsh - the structure containing all player entity data, type Arsh*

Output: Output: arsh - the structure containing all player entity data, type Arsh*
*/
void doArshSlide(struct Arsh* arsh)
{
	if(arsh->timeInState < SLIDE_LENGTH)
	{
		arsh->timeInState++;
	}
	else
	{
		setArshRun(arsh);
	}
	
	return;
}


/*
Name: doArshKick

Purpose: performs 1 frame of the arsh kick action

Input: arsh - the structure containing all player entity data, type Arsh*

Output: arsh - the structure containing all player entity data, type Arsh*
*/
void doArshKick(struct Arsh* arsh)
{
	if(arsh->timeInState < KICK_LENGTH)
	{
		arsh->timeInState++;
	}
	else
	{
		setArshRun(arsh);
	}
	
	return;
}


/*
Name: doArshJumpRise

Purpose: performs 1 frame of the arsh jump rise action

Input: arsh - the structure containing all player entity data, type Arsh*

Output: arsh - the structure containing all player entity data, type Arsh*

Details: sub action of the arsh jump action
*/
void doArshJumpRise(struct Arsh* arsh)
{
	arsh->y1 -= arsh->yVelocity;
	arsh->y2 -= arsh->yVelocity;
	
	return;
}


/*
Name: doArshJumpHang

Purpose: performs 1 frame of the arsh jump hang action

Input: arsh - the structure containing all player entity data, type Arsh*

Output: arsh - the structure containing all player entity data, type Arsh*

Details: sub action of the arsh jump action
*/
void doArshJumpHang(struct Arsh* arsh)
{
	/* maybe animation stuff */
	
	return;
}


/*
Name: doArshJumpFall

Purpose: performs 1 frame of the arsh jump fall action

Input: arsh - the structure containing all player entity data, type Arsh*

Output: arsh - the structure containing all player entity data, type Arsh*

Details: sub action of the arsh jump action
*/
void doArshJumpFall(struct Arsh* arsh)
{
	arsh->y1 += arsh->yVelocity;
	arsh->y2 += arsh->yVelocity;
	
	return;
}

/*
Name: resetCloud

Purpose: resets a cloud from the left side of the screen, to the right

Input: cloud - the structure containing all cloud entity data, type Cloud*

Output: cloud - the structure containing all cloud entity data, type Cloud*

Details: randomly assigns the cloud a velocity between 1 and MAX_CLOUD_SPEED
*/
void resetCloud(struct Cloud* cloud)
{
	int speed;
	
	speed = rand() % MAX_CLOUD_SPEED;
	
	cloud->x = OBSTACLE_DEACTIVATED_LEFT;
	cloud->velocity = speed + 1;
	
	return;
}

/*
Name: spawnObstacle

Purpose: randomly selects what type of object and its parameters,
		 enables it and moves it to the game world
		 
Input: obstacle - the structure containing the data for one obstacle entity, type Obstacle*
       obstacleVelocity - the global obstacle velocity property from the model, type UINT8
	   
Output: obstacle - the structure containing the data for one obstacle entity, type Obstacle*
	   
Details: Possible obstacles are Hay Bales, Cacti, or Vultures
*/
void spawnObstacle(struct Obstacle* obstacle, UINT8 obstacleVelocity)
{
	int obstacleType;
	
	obstacleType = rand() % OBSTACLE_NUM_TYPES;
	
	switch(obstacleType)
	{
		case 0:
			spawnObstacleBale(obstacle, obstacleVelocity);
			break;
		case 1:
			spawnObstacleCactus(obstacle, obstacleVelocity);
			break;
		case 2:
			spawnObstacleVulture(obstacle, obstacleVelocity);
			break;
	}
	
	return;
}


/*
Name: spawnObstacleBale

Purpose: sets the obstacle's attributes to those of a bale,
		 and moves it to the game world
		 
Input: obstacle - the structure containing the data for one obstacle entity, type Obstacle*
       obstacleVelocity - the global obstacle velocity property from the model, type UINT8
	   
Output: obstacle - the structure containing the data for one obstacle entity, type Obstacle*
	   
Details: sub function of spawnObstacle
*/
void spawnObstacleBale(struct Obstacle* obstacle, UINT8 obstacleVelocity)
{
	obstacle->type = bale;
	/* dont set x1 because it should be in holding zone */
	obstacle->x2 = obstacle->x1 + OBSTACLE_BALE_WIDTH - 1;
	obstacle->y1 = OBSTACLE_BALE_TOP;
	obstacle->y2 = obstacle->y1 + OBSTACLE_BALE_HEIGHT - 1;
	obstacle->velocity = obstacleVelocity;
	obstacle->kickable = FALSE;
	obstacle->kicked = FALSE;
	obstacle->enabled = TRUE;
	
	return;
}


/*
Name: spawnObstacleCactus

Purpose: sets the obstacle's attributes to those of a cactus,
		 and moves it to the game world
		 
Input: obstacle - the structure containing the data for one obstacle entity, type Obstacle*
       obstacleVelocity - the global obstacle velocity property from the model, type UINT8
	   
Output: obstacle - the structure containing the data for one obstacle entity, type Obstacle*
	   
Details: sub function of spawnObstacle
*/
void spawnObstacleCactus(struct Obstacle* obstacle, UINT8 obstacleVelocity)
{
	obstacle->type = cactus;
	/* dont set x1 because it should be in holding zone */
	obstacle->x2 = obstacle->x1 + OBSTACLE_CACTUS_WIDTH - 1;
	obstacle->y1 = OBSTACLE_CACTUS_TOP;
	obstacle->y2 = obstacle->y1 + OBSTACLE_CACTUS_HEIGHT - 1;
	obstacle->velocity = obstacleVelocity;
	obstacle->kickable = TRUE;
	obstacle->kicked = FALSE;
	obstacle->enabled = TRUE;
	
	return;
}


/*
Name: spawnObstacleVulture

Purpose: sets the obstacles attributes to those of a vulture,
		 and moves it to the game world
		 
Input: obstacle - the structure containing the data for one obstacle entity, type Obstacle*
	   obstacleVelocity - the global obstacle velocity property from the model, type UINT8
	   
Output: obstacle - the structure containing the data for one obstacle entity, type Obstacle*

Details: sub function of spawnObstacle
*/
void spawnObstacleVulture(struct Obstacle* obstacle, UINT8 obstacleVelocity)
{
	obstacle->type = vulture;
	/* dont set x1 because it should be in holding zone */
	obstacle->x2 = obstacle->x1 + OBSTACLE_VULTURE_WIDTH - 1;
	obstacle->y1 = OBSTACLE_VULTURE_TOP;
	obstacle->y2 = obstacle->y1 + OBSTACLE_VULTURE_HEIGHT - 1;
	obstacle->velocity = obstacleVelocity;
	obstacle->kickable = FALSE;
	obstacle->kicked = FALSE;
	obstacle->enabled = TRUE;
	
	return;
}

/*
Name: moveObstacle

Purpose: if the obstacle is enabled, moves it velocity pixels to the left
		 if it goes off the left side of the screen, removes it and increments
		 the score
		 
Input: obstacle - the structure containing the data for one obstacle entity, type Obstacle*
	   score - the structure containing the data for the score entity, type Score*
	   spawnRate - the global obstacle spawnRate property from the model, type UINT8*
	   obstacleVelocity - the global obstacle velocity property from the model, type UINT8*
	   
Output: Input: obstacle - the structure containing the data for one obstacle entity, type Obstacle*
	    score - the structure containing the data for the score entity, type Score*
	    spawnRate - the global obstacle spawnRate property from the model, type UINT8*
	    obstacleVelocity - the global obstacle velocity property from the model, type UINT8*
*/
void moveObstacle(struct Obstacle* obstacle, struct Score* score, UINT8* spawnRate, UINT8* obstacleVelocity)
{
	if(obstacle->enabled)
	{
		obstacle->x1 -= obstacle->velocity;
		obstacle->x2 -= obstacle->velocity;
		
		if(obstacle->x2 < 0)
		{
			removeObstacle(obstacle);
			incrementScore(score, spawnRate, obstacleVelocity);
		}
	}
	
	return;
}


/*
Name: removeObstacle

Purpose: disables an obstacle and removes it from the game world

Input: obstacle - the structure containing the data for one obstacle entity, type Obstacle*

Output: obstacle - the structure containing the data for one obstacle entity, type Obstacle*

Details: doesn't actually delete the obstacle, just hides it offscreen until it's needed
*/
void removeObstacle(struct Obstacle* obstacle)
{
	obstacle->x1 = OBSTACLE_DEACTIVATED_LEFT;
	obstacle->x2 = OBSTACLE_DEACTIVATED_LEFT;
	obstacle->y1 = OBSTACLE_DEACTIVATED_TOP;
	obstacle->y2 = OBSTACLE_DEACTIVATED_TOP;
	obstacle->velocity = 0;
	obstacle->enabled = FALSE;
	
	return;
}

/*
Name: moveCloud

Purpose: moves the cloud by velocity pixels to the left,
		 resets it if it moves offscreen
		 
Input: cloud - the structure containing all cloud entity data, type Cloud*

Output: cloud - the structure containing all cloud entity data, type Cloud*
*/
void moveCloud(struct Cloud* cloud)
{
	cloud->x -= cloud->velocity;
	if(cloud->x + CLOUD_WIDTH < 0)
	{
		resetCloud(cloud);
	}
	
	return;
}


/*
Name: moveTumbleweed

Purpose: moves the tumbleweed by velocity pixels to the left,
		 hides it once it moves offscreen
		 
Input: weed - the structure containing all tumbleweed entity data, type Tumbleweed*

Output: weed - the structure containing all tumbleweed entity data, type Tumbleweed*
*/
void moveTumbleweed(struct Tumbleweed* weed)
{
	if(weed->enabled)
	{
		weed->x -= weed->velocity;
		if(weed->x + TUMBLEWEED_WIDTH < 0)
		{
			weed->enabled = FALSE;
		}
	}
	
	return;
}


/*
Name: incrementScore

Purpose: increments the score by 1, and updates the model obstacle spawnRate and
		 obstacle velocity when the score reaches certain thresholds
		 
Input: score - the structure containing the data for the score entity, type Score*
	   spawnRate - the global obstacle spawnRate property from the model, type UINT8*
	   obstacleVelocity - the global obstacle velocity property from the model, type UINT8*
	   
Output: score - the structure containing the data for the score entity, type Score*
	    spawnRate - the global obstacle spawnRate property from the model, type UINT8*
	    obstacleVelocity - the global obstacle velocity property from the model, type UINT8*
*/
void incrementScore(struct Score* score, UINT8* spawnRate, UINT8* obstacleVelocity)
{
	if(score->scoreValue < 9999)
	{
		score->scoreValue++;
		if(score->scoreValue == SCORE_THRESHOLD_1)
		{
			 *obstacleVelocity = PHASE_2_VELOCITY;
			 *spawnRate = PHASE_2_SPAWNRATE;
		}
		else if(score->scoreValue == SCORE_THRESHOLD_2)
		{
			 *obstacleVelocity = PHASE_3_VELOCITY;
			 *spawnRate = PHASE_3_SPAWNRATE;
		}
		else if(score->scoreValue == SCORE_THRESHOLD_3)
		{
			 *obstacleVelocity = PHASE_4_VELOCITY;
			 *spawnRate = PHASE_4_SPAWNRATE;
		}
		   
	}
	
	return;
}


/*
Name: checkCollision

Purpose: checks if an obstacle has collided with arsh,
		 if it has, kills him
		 
Input: arsh - the structure containing all player entity data, type Arsh*
	   obstacle - the structure containing the data for one obstacle entity, type Obstacle*
	   
Output: arsh - the structure containing all player entity data, type Arsh*
	    obstacle - the structure containing the data for one obstacle entity, type Obstacle*
		 
Details: if the obstacle is kickable and arsh is kicking, 
		 destroys the obstacle instead
*/
void checkCollision(struct Arsh* arsh, struct Obstacle* obstacle)
{
	if(obstacle->enabled)
	{
		if(!obstacle->kicked)
		{
			if( (arsh->x2 >= obstacle->x1 && arsh->x2 <= obstacle->x2) ||
				(arsh->x1 >= obstacle->x1 && arsh->x1 <= obstacle->x2) )
			{
				if( (arsh->y2 >= obstacle->y1 && arsh->y2 <= obstacle->y2) ||
					(arsh->y1 >= obstacle->y1 && arsh->y1 <= obstacle->y2) )
				{
					if(obstacle->kickable && arsh->state == kick)
					{
						obstacle->kicked = TRUE;
						obstacle->y1 = OBSTACLE_CACTUS_DEST_TOP;
						playKickEffect();
					}
					else
					{
						arsh->alive = FALSE;
					}
				}
			}
		}
	}

	return;
}



/*
Name: checkMouseOver
Purpose: checks if the mouse is hovering over a button
Input: button - the button in question, type Button*
	   mouseX - the x coordinate of the mouse, type int
	   mouseY - the y coordinate of the mouse, type int
Return value: whether or not the mouse in in the button's hitbox, type UINT8
*/
UINT8 checkMouseOver(struct Button* button, int mouseX, int mouseY)
{

	return (mouseX >= button->x1 && mouseX <= button->x2) &&
		   (mouseY >= button->y1 && mouseY <= button->y2);
}