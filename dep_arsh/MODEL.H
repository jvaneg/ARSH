/*
Names: 	Joel v
		Kieran K

Module: Model 

Purpose: The model module is used for all of the structures that are 
		contained within the model of the game, and the functions that directly
		impact the model. 

Details: The model is not responsible for updating the position of objects within the
		model, and the model functions should only be used when the appropriate 
		asynchronous command is given by the user. 
*/

#ifndef MODEL_H
#define MODEL_H

#include "types.h"
#include "sound_ef.h"

#define TRUE 1
#define FALSE 0

#define MAX_OBSTACLES 2

/* Arsh Constants */ 
#define ARSH_STANDARD_WIDTH 34
#define ARSH_STANDARD_HEIGHT 96
#define ARSH_STANDARD_TOP 223
#define ARSH_STANDARD_BOTTOM 319
#define ARSH_STANDARD_LEFT 94
#define ARSH_STANDARD_RIGHT 127
#define ARSH_SPRITE_STD_LEFT 79

#define ARSH_SLIDE_HEIGHT 60
#define ARSH_SLIDE_TOP 259
#define ARSH_SPRITE_SLIDE_LEFT 55

#define ARSH_KICK_WIDTH 64
#define ARSH_KICK_RIGHT 142

/* Cloud constants */
#define CLOUD_WIDTH 64
#define CLOUD_HEIGHT 45
#define CLOUD_TOP 80

/* Tumbleweed constants */
#define TUMBLEWEED_WIDTH 64
#define TUMBLEWEED_HEIGHT 64

/* Background constants */
#define BG_SUN_LEFT 50
#define BG_SUN_TOP 5
#define BG_SUN_HEIGHT 64
#define BG_STAGE_TOP 320
#define BG_STAGE_HEIGHT 80

/* Obstacle constants */
#define OBSTACLE_CACTUS_WIDTH 32
#define OBSTACLE_CACTUS_HEIGHT 128
#define OBSTACLE_CACTUS_TOP 192
#define OBSTACLE_CACTUS_BOTTOM 319

#define OBSTACLE_CACTUS_DEST_HEIGHT 53
#define OBSTACLE_CACTUS_DEST_TOP 267

#define OBSTACLE_VULTURE_HEIGHT 32
#define OBSTACLE_VULTURE_WIDTH 64
#define OBSTACLE_VULTURE_TOP 207
#define OBSTACLE_VULTURE_BOTTOM 239

#define OBSTACLE_BALE_HEIGHT 64
#define OBSTACLE_BALE_WIDTH 64
#define OBSTACLE_BALE_TOP 256
#define OBSTACLE_BALE_BOTTOM 319

#define OBSTACLE_DEACTIVATED_TOP 239
#define OBSTACLE_DEACTIVATED_LEFT 640

#define OBSTACLE_NUM_TYPES 3
#define OBSTACLE_VELOCITY 10

/* Spawnrate constants */
#define OBSTACLE_START_SPAWNRATE 60

/* Scorebox constants */
#define SCOREBOX_WIDTH 120
#define SCOREBOX_HEIGHT 20
#define SCOREBOX_LEFT 0
#define SCOREBOX_TOP 379
#define SCOREBOX_RESPECT_HEIGHT 14
#define SCOREBOX_RESPECT_WIDTH 64

#define SCOREBOX_SCORE_LEFT 70

/* Menu constants */
#define MENU_SPACE_BETWEEN_BUTTONS 24
#define MENU_MAX_BUTTONS 3

#define ONEPLAYER_LEFT 288
#define ONEPLAYER_TOP 309
#define ONEPLAYER_RIGHT 349
#define ONEPLAYER_BOTTOM 322

#define TWOPLAYER_LEFT 288
#define TWOPLAYER_TOP 333
#define TWOPLAYER_RIGHT 349
#define TWOPLAYER_BOTTOM 346

#define QUIT_LEFT 288
#define QUIT_TOP 357
#define QUIT_RIGHT 317
#define QUIT_BOTTOM 368

#define ARROW_WIDTH 8
#define ARROW_AREA_HEIGHT 60

#define MENU_MAX_SELECTION 2

/* Endscreen constants */
#define ENDSCREEN_MAX_SELECTION 1
#define ENDSCREEN_MAX_BUTTONS 2

#define END_ARROW_AREA_HEIGHT 36

#define MAIN_LEFT 288
#define MAIN_TOP 333
#define MAIN_RIGHT 358
#define MAIN_BOTTOM 344

#define END_SCORE_TOP 156
#define END_SCORE_LEFT 346

enum ArshState {run,jump,slide,kick};
 
enum ObstacleType {bale, cactus, vulture};


struct Arsh
{
	int x1, y1; /* top left of hitbox */
	int x2, y2; /* bottom right of hitbox */
	int xSprite; /* top left of sprite */
	int timeInState;
	int yVelocity;
	enum ArshState state;
	UINT8 alive;
	UINT8 skin;
};

struct Obstacle
{
	enum ObstacleType type;
	int x1, y1; /* top left of hitbox */
	int x2, y2; /* bottom right of hitbox */
	UINT8 velocity;
	UINT8 kickable;
	UINT8 kicked;
	UINT8 enabled;
};

struct ScoreBox
{
	int x, y; /* top left of sprite */
};

struct Score
{
	int x, y; /* top left of sprite */
	int scoreValue;
};

struct Tumbleweed
{
	int x, y; /* top left of sprite */
	int velocity;
	UINT8 enabled;
};

struct Cloud
{
	int x, y; /* top left of sprite */
	int velocity;
};

struct Background
{
	int sunX, sunY; /* top left of sun */
	int stageY;
	int stageHeight;
};

struct Music
{
	int currentNote;
	UINT8 bChannelActivated;
};

struct Model
{
	struct Arsh arsh;
	struct Obstacle obstacles[MAX_OBSTACLES];
	struct ScoreBox scoreBox;
	struct Score score;
	struct Tumbleweed weed;
	struct Cloud cloud;
	struct Background background;
	struct Music music;
	UINT8 spawnRate;
	UINT8 obstacleVelocity;
};

/* MENU MODEL */

struct Button
{
	int x1, y1; /* top left of hitbox */
	int x2, y2; /* bottom right of hitbox */
};

struct SelectArrow
{
	int x, y; /* top left of sprite */
    UINT8 selected; /* which button is currently selected */
};

struct MenuModel
{
	struct Button buttons[MENU_MAX_BUTTONS]; /* the 1-player, 2-player, and quit buttons */ 
    struct SelectArrow selectArrow; /* the selection arrow */
    int mouseX;
    int mouseY;
    int oldMouseX;
    int oldMouseY;
};

/* ENDSCREEN MODEL */

struct EndscreenModel
{
	struct Button buttons[ENDSCREEN_MAX_BUTTONS]; /* the main menu and quit buttons */
	struct SelectArrow selectArrow; /* the selection arrow */
	struct Score finalScore;        /* the final score */
    int mouseX;
    int mouseY;
    int oldMouseX;
    int oldMouseY;
};

/* FUNCTION PROTOTYPES */

void setArshRun(struct Arsh* arsh);
void setArshJump(struct Arsh* arsh);
void setArshSlide(struct Arsh* arsh);
void setArshKick(struct Arsh* arsh);
void swapArshSkin(struct Arsh* arsh);

void moveSelectionUp(struct SelectArrow* arrow);
void moveSelectionDown(struct SelectArrow* arrow, int maxSelection);

#endif
