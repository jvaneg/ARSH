/*
Names: 	Joel v
		Kieran K

Module: Renderer 
*/

#include "renderer.h"
#include "sprites.h"
#include "sprites2.h"


/*
Name: renderArsh

Purpose: draws arsh to the screen based off his current state and position

Input: arsh - the structure containing all player entity data, type Arsh*
	   base - pointer to the start of the frame buffer, type UINT32*
*/
void renderArsh(const struct Arsh* arsh, UINT32* base)
{
	int height;
	height = (arsh->y2 - arsh->y1 + 1);
	
	switch(arsh->state)
	{
		case run:
			/*
			POSSIBLE CODE FOR VARIETY FOR TWO DIFFERENT FRAMES OF ARSH RUNNING
			
			if((arsh->timeInState % 20) < 10)
			{
				plotBitmap64(base, arsh->xSprite, arsh->y1, bmp_arsh_run_64, height);
			}
			else
			{
				plotBitmap64(base, arsh->xSprite, arsh->y1, bmp_arsh_run_2_64, height);
			}
			*/
			if(arsh->skin)
			{
				plotBitmap64(base, arsh->xSprite, arsh->y1, bmp_arsh_run_64, height-1);
			}
			else
			{
				plotBitmap64(base, arsh->xSprite, arsh->y1, bmp_bad_bandit_run_64, height-1);
			}
			
			break;
		
		case jump:
			if(arsh->skin)
			{
				plotBitmap64(base, arsh->xSprite, arsh->y1, bmp_arsh_jump_64, height-1);
			}
			else
			{
				plotBitmap64(base, arsh->xSprite, arsh->y1, bmp_bad_bandit_jump_64, height-1);
			}
			break;
			
		case kick:
			if(arsh->skin)
			{
				plotBitmap64(base, arsh->xSprite, arsh->y1, bmp_arsh_kick_64, height-1);
			}
			else
			{
				plotBitmap64(base, arsh->xSprite, arsh->y1, bmp_bad_bandit_kick_64, height-1);
			}
			break;

		case slide:
			if(arsh->skin)
			{
				plotBitmap96(base, arsh->xSprite, arsh->y1, bmp_arsh_slide_96, height-1);
			}
			else
			{
				plotBitmap96(base, arsh->xSprite, arsh->y1, bmp_bad_bandit_slide_96, height-1);
			}
			break;
	}
	
}

/*
Name: renderObstacle

Purpose: draws an obstacle to the screen based off its current position, type and state (if cactus)

Input: obstacle - the structure containing all obstacle data, type Obstacle*
	   base - pointer to the start of the frame buffer, type UINT32*
*/
void renderObstacle(const struct Obstacle* obstacle, UINT32* base)
{
	int height;
	height = (obstacle->y2 - obstacle->y1 + 1);
	
    if(obstacle->enabled)
    {
        switch(obstacle->type)
        {
            case bale:
				plotBitmap64(base, obstacle->x1, obstacle->y1, bmp_haybale_64, height);
                break;
            
            case cactus:
                if(!obstacle->kicked)
                {
					plotBitmap32(base, obstacle->x1, obstacle->y1, bmp_cactus_32, height);
                }
                else
                {
					plotBitmap32(base, obstacle->x1, obstacle->y1, bmp_cactus_dead_32, height);
                }
                break;
                
            case vulture:
				plotBitmap64(base, obstacle->x1, obstacle->y1, bmp_vulture_64, height);
                break;

        }
    }

}

/*
Name: renderScoreBox

Purpose: draws a space for the scoreBox on the screen, based off the size of the scoreBox

Input: scoreBox - the structure containing all score box data, type ScoreBox*
	   base - pointer to the start of the frame buffer, type UINT32*
*/
void renderScoreBox(const struct ScoreBox* scoreBox, UINT32* base)
{
	clearRectangle((UINT8*) base, scoreBox->x, scoreBox->y, SCOREBOX_WIDTH, SCOREBOX_HEIGHT);
    
    plotBitmap64(base, scoreBox->x, scoreBox->y + 3, bmp_respect_64, SCOREBOX_RESPECT_HEIGHT);
}

/*
Name: renderScore

Purpose: draws the integer value of the score to the screen based off the position and 
		 value of the score

Input: score - the structure containing all score data, type Score*
	   base - pointer to the start of the frame buffer, type UINT8*
*/
void renderScore(const struct Score* score, UINT8* base)
{
	int updatedScore;
	clearRectangle(base, score->x, score->y, 32, 14);
	
	if(score->scoreValue / 10 == 0)
	{
		plotDigit8(base, score->x, score->y, digits, score->scoreValue);
	}
	else if(score->scoreValue / 100 == 0)
	{
		plotDigit8(base, score->x, score->y, digits, (score->scoreValue / 10));
		plotDigit8(base, score->x + 8, score->y, digits, (score->scoreValue % 10));
	}
	else if(score->scoreValue / 1000 == 0)
	{
		plotDigit8(base, score->x, score->y, digits, (score->scoreValue / 100));
		plotDigit8(base, score->x + 8, score->y, digits, (score->scoreValue / 10) % 10);
		plotDigit8(base, score->x + 16, score->y, digits, (score->scoreValue % 10));
	}
	else
	{
		plotDigit8(base, score->x, score->y, digits, (score->scoreValue / 1000));
		plotDigit8(base, score->x + 8, score->y, digits, (score->scoreValue / 100) % 10);
		plotDigit8(base, score->x + 16, score->y, digits, (score->scoreValue / 10) % 10);
		plotDigit8(base, score->x + 24, score->y, digits, score->scoreValue % 10);
	}
}

/*
Name: renderTumbleweed

Purpose: draws a tumbleweed to the screen based off its current position

Input: weed - the structure containing all of the tumbleweed data, type Tumbleweed*
	   base - pointer to the start of the frame buffer, type UINT32*
*/
void renderTumbleweed(const struct Tumbleweed* weed, UINT32* base)
{
	plotBitmap64(base, weed->x, weed->y, bmp_tumbleweed_64, TUMBLEWEED_HEIGHT);
}

/*
Name: renderCloud

Purpose: draws a cloud to the screen based off its current position

Input: cloud - the structure containing all of the cloud data, type Cloud*
	   base - pointer to the start of the frame buffer, type UINT32*
*/
void renderCloud(const struct Cloud* cloud, UINT32* base)
{
	plotBitmap64(base, cloud->x, cloud->y, bmp_cloud_64, CLOUD_HEIGHT);
}

/*
Name: renderBackground

Purpose: draws the background of the gameplay areas, including a large black rectangle
		 on the bottom of the screen, and a cool sun in the sky

Input: bg - the structure containing all of the background data, type Background*
	   base - pointer to the start of the frame buffer, type UINT32*
*/
void renderBackground(const struct Background* bg, UINT32* base)
{
    plotBitmap64(base, bg->sunX, bg->sunY, bmp_sun_64, BG_SUN_HEIGHT);
    
    fillRectangle((UINT8*) base, 0, bg->stageY, SCREEN_WIDTH, bg->stageHeight);
}

/*
Name: renderFull

Purpose: draws the full gamescreen, including the background, intended to be used once
		at the start of the game

Input: model - the structure containing all of the model data, type Model*
	   base - pointer to the start of the frame buffer, type UINT32*
*/
void renderFull(const struct Model* model, UINT32* base)
{
    int obstacleIndex;
    
    clear_screen(base);
	
    renderBackground(&model->background, base);
    
    renderArsh(&model->arsh, base);
    
    for(obstacleIndex = 0; obstacleIndex < MAX_OBSTACLES; obstacleIndex++)
    {
        renderObstacle(&model->obstacles[obstacleIndex], base);
    }
	
	renderScoreBox(&model->scoreBox, base);
	renderScore(&model->score, (UINT8*) base);
    
    renderCloud(&model->cloud, base);
	renderTumbleweed(&model->weed, base);
}

/*
Name: renderUpdate

Purpose: draws the full gameplay area, intended to be each time after the model
		is updated

Input: model - the structure containing all of the model data, type Model*
	   base - pointer to the start of the frame buffer, type UINT32*
*/
void renderUpdate(const struct Model* model, UINT32* base)
{
	int obstacleIndex;
    
    clear_playarea(base);
    
    renderArsh(&model->arsh, base);
    
    for(obstacleIndex = 0; obstacleIndex < MAX_OBSTACLES; obstacleIndex++)
    {
        renderObstacle(&model->obstacles[obstacleIndex], base);
    }
	
	renderScore(&model->score, (UINT8*) base);
    
    renderCloud(&model->cloud, base);
	if(model->weed.enabled)
	{
		renderTumbleweed(&model->weed, base);
	}
}


/* MENU RENDERING */

/*
Name: renderMenuFull

Purpose: draws the full menu screen, including the background, intended to be used once
		at the start of the menu load

Input: menu - the structure containing all of the menu model data, type MenuModel*
	   base - pointer to the start of the frame buffer, type UINT32*
*/
void renderMenuFull(const struct MenuModel* menu, UINT32* base)
{
	clear_screen(base);
	
    plotBitmapFullscreen(base, bmp_menu);
    
    renderMenuArrow(&menu->selectArrow, (UINT8*) base);
    
    renderMenuMouse((UINT8*) base, menu->mouseX, menu->mouseY);
}

/*
Name: renderMenuUpdate

Purpose: redraws the menu select arrow, intended to be used each time after the menu model
		is updated

Input: menu - the structure containing all of the model data, type MenuModel*
	   base - pointer to the start of the frame buffer, type UINT32*
*/
void renderMenuUpdate(const struct MenuModel* menu, UINT32* base)
{
    renderMenuMouse((UINT8*) base, menu->oldMouseX, menu->oldMouseY);
    
    clearRectangle((UINT8*) base, menu->buttons[0].x1 - 12, menu->buttons[0].y1 + 1, ARROW_WIDTH, ARROW_AREA_HEIGHT);
    
    renderMenuMouse((UINT8*) base, menu->mouseX, menu->mouseY);
	
    renderMenuArrow(&menu->selectArrow, (UINT8*) base);
}

/*
Name: renderMenuArrow

Purpose: draws the menu selection arrow

Input: arrow - the structure containing the arrow information, type SelectArrow*
       base - pointer to the start of the frame buffer, type UINT8*
*/
void renderMenuArrow(const struct SelectArrow* arrow, UINT8* base)
{
	plotBitmap8(base, arrow->x, arrow->y, bmp_select_arrow, 9);
}

/*
Name: renderMenuMouse

Purpose: draws the mouse (may also be used to undraw the cursor because its a xor)

Input: base - pointer to the start of the frame buffer, type UINT8*
	   mouseX - mouse X coordinate, type int
	   mouseY - mouse Y coordinate, type int

Details: uses global mouse x and y coordinates from the IKBD buffer
         Cursor dissapears into the sunset following this curve:
               Y    |   CURSOR ROWS
            - 220   |       0
            - 230   |       1
            - 244   |       2
            - 257   |       3
            - 271   |       4
            - 286   |       5
            - 303   |       6
            - 321   |       7
            - 345   |       8
            - 400   |       9
*/
void renderMenuMouse(UINT8* base, int mouseX, int mouseY)
{
    if(mouseY > 220){
        xorHorizontalLine(base, mouseX, mouseY++, 1);
        if(mouseY > 230){
            xorHorizontalLine(base, mouseX, mouseY++, 2);
            if(mouseY > 244){
                xorHorizontalLine(base, mouseX, mouseY++, 2);
                if(mouseY > 257){
                    xorHorizontalLine(base, mouseX, mouseY++, 3);
                    if(mouseY > 271){
                        xorHorizontalLine(base, mouseX, mouseY++, 3);
                        if(mouseY > 286){
                            xorHorizontalLine(base, mouseX, mouseY++, 4);
                            if(mouseY > 303){
                                xorHorizontalLine(base, mouseX, mouseY++, 4);
                                if(mouseY > 321){
                                    xorHorizontalLine(base, mouseX, mouseY++, 4);
                                    if(mouseY > 345){
                                        xorHorizontalLine(base, mouseX, mouseY++, 5);
    }}}}}}}}}
}


/* ENDSCREEN RENDERING */

/*
Name: renderEndscreenFull

Purpose: draws the full endscreen, including the background, intended to be used once
		at the start of the endscreen load

Input: endscreen - the structure containing all of the endscreen model data, type EndscreenModel*
	   base - pointer to the start of the frame buffer, type UINT32*
*/
void renderEndscreenFull(const struct EndscreenModel* endscreen, UINT32* base)
{
	clear_screen(base);
	
    plotBitmapFullscreen(base, bmp_endscreen);
	
	renderScore(&endscreen->finalScore, (UINT8*) base);
    
    renderMenuArrow(&endscreen->selectArrow, (UINT8*) base);
    
    renderEndMouse((UINT8*) base, endscreen->mouseX, endscreen->mouseY);
}

/*
Name: renderEndscreenUpdate

Purpose: redraws the endscreen select arrow, intended to be used each time after the endscreen model
		is updated

Input: menu - the structure containing all of the endscreen model data, type EndscreenModel*
	   base - pointer to the start of the frame buffer, type UINT32*
*/
void renderEndscreenUpdate(const struct EndscreenModel* endscreen, UINT32* base)
{
    renderEndMouse((UINT8*) base, endscreen->oldMouseX, endscreen->oldMouseY);
    
	clearRectangle((UINT8*) base, endscreen->buttons[0].x1 - 12, endscreen->buttons[0].y1 + 1, ARROW_WIDTH, END_ARROW_AREA_HEIGHT);
    
    renderEndMouse((UINT8*) base, endscreen->mouseX, endscreen->mouseY);
	
    renderMenuArrow(&endscreen->selectArrow, (UINT8*) base);
}


/*
Name: renderEndMouse

Purpose: draws the mouse (may also be used to undraw the cursor because its a xor)

Input: base - pointer to the start of the frame buffer, type UINT8*
	   mouseX - mouse X coordinate, type int
	   mouseY - mouse Y coordinate, type int

Details: uses global mouse x and y coordinates from the IKBD buffer
         Cursor dissapears into the sunset following this curve:
               Y    |   CURSOR ROWS
            - 270   |       0
            - 276   |       1
            - 286   |       2
            - 296   |       3
            - 307   |       4
            - 318   |       5
            - 330   |       6
            - 344   |       7
            - 361   |       8
*/
void renderEndMouse(UINT8* base, int mouseX, int mouseY)
{
    if(mouseY > 270){
        xorHorizontalLine(base, mouseX, mouseY++, 1);
        if(mouseY > 276){
            xorHorizontalLine(base, mouseX, mouseY++, 2);
            if(mouseY > 286){
                xorHorizontalLine(base, mouseX, mouseY++, 2);
                if(mouseY > 296){
                    xorHorizontalLine(base, mouseX, mouseY++, 3);
                    if(mouseY > 307){
                        xorHorizontalLine(base, mouseX, mouseY++, 3);
                        if(mouseY > 318){
                            xorHorizontalLine(base, mouseX, mouseY++, 4);
                            if(mouseY > 330){
                                xorHorizontalLine(base, mouseX, mouseY++, 4);
                                if(mouseY > 344){
                                    xorHorizontalLine(base, mouseX, mouseY++, 4);
                                    if(mouseY > 361){
                                        xorHorizontalLine(base, mouseX, mouseY++, 5);
    }}}}}}}}}
}

/*
Name: renderPaul
Purpose: renders a SICK paul image
Input: base - pointer to the start of the frame buffer, type UINT32*
*/
void renderPaul(UINT32* base)
{
	int x = rand() % 640;
	int y = rand() % 400;
	
	xorBitmap64(base, x, y, bmp_paul_64, 64);
}

/*
Name: renderAllPauls
Purpose: renders a bunch of SICK paul images
Input: base - pointer to the start of the frame buffer, type UINT32*
*/
void renderAllPauls(UINT32* base)
{
	int index;
	long i2;
	
	for(index = 0; index < 5; index++)
	{
		renderPaul(base);
		for(i2 = 0; i2 < 150000; i2++);
	}
	
	for(index = 0; index < 1000; index++)
	{
		renderPaul(base);
	}
}

