/*
Name:   Joel v
        Kieran K

Module: Model 
*/

#include "model.h"


/*
Name: setArshRun

Purpose: puts Arsh in the run state

Input: arsh - the structure containing all player entity data, type Arsh*

Output: arsh - the structure containing all player entity data, type Arsh*
*/
void setArshRun(struct Arsh* arsh)
{
    if(arsh->state != run)
    {
        arsh->state = run;
        arsh->timeInState = 0;
        arsh->yVelocity = 0;
        
        arsh->x1 = ARSH_STANDARD_LEFT;
        arsh->x2 = ARSH_STANDARD_RIGHT;
        arsh->y1 = ARSH_STANDARD_TOP;
        arsh->y2 = ARSH_STANDARD_BOTTOM;
        
        arsh->xSprite = ARSH_SPRITE_STD_LEFT;
    }
    
}


/*
Name: setArshJump

Purpose: puts Arsh in the jump state

Input: arsh - the structure containing all player entity data, type Arsh*

Output: arsh - the structure containing all player entity data, type Arsh*
*/
void setArshJump(struct Arsh* arsh)
{
    if(arsh->state == run)
    {
        arsh->state = jump;
        arsh->timeInState = 0;
        arsh->yVelocity = 14;
        startJumpEffect();
    }
    
}


/*
Name: setArshSlide

Purpose: puts Arsh in the slide state

Input: arsh - the structure containing all player entity data, type Arsh*

Output: arsh - the structure containing all player entity data, type Arsh*
*/
void setArshSlide(struct Arsh* arsh)
{
    if(arsh->state == run)
    {
        arsh->state = slide;
        arsh->timeInState = 0;
        
        arsh->y1 = ARSH_SLIDE_TOP;
        
        arsh->xSprite = ARSH_SPRITE_SLIDE_LEFT;
        playSlideEffect();
    }
    
}
/*
Name: setArshKick

Purpose: puts Arsh in the kick state

Input: arsh - the structure containing all player entity data, type Arsh*

Output: arsh - the structure containing all player entity data, type Arsh*
*/
void setArshKick(struct Arsh* arsh)
{
    if(arsh->state == run)
    {
        arsh->state = kick;
        arsh->timeInState = 0;
        
        arsh->x2 = ARSH_KICK_RIGHT;
    }
}


/*
Name: swapArshSkin

Purpose: swaps Arsh's sprite with that of the bad bandit

Input: arsh - the structure containing all player entity data, type Arsh*

Output: arsh - the structure containing all player entity data, type Arsh*
*/
void swapArshSkin(struct Arsh* arsh)
{
    arsh->skin = !(arsh->skin);
}


/* MENU MODEL FUNCTIONS */


/*
Name: moveSelectionUp

Purpose: moves the selection arrow up by one option

Input: arrow - the structure containing all arrow entity data, type SelectArrow*

Output: arrow - the structure containing all arrow entity data, type SelectArrow*
*/
void moveSelectionUp(struct SelectArrow* arrow)
{
    if( arrow->selected != 0)
    {
        arrow->selected--;
        arrow->y -= MENU_SPACE_BETWEEN_BUTTONS;
    }
}


/*
Name: moveSelectionDown

Purpose: moves the selection arrow down by one option

Input: arrow - the structure containing all arrow entity data, type SelectArrow*

Output: arrow - the structure containing all arrow entity data, type SelectArrow*
*/
void moveSelectionDown(struct SelectArrow* arrow, int maxSelection)
{
    if( arrow->selected != maxSelection)
    {
        arrow->selected++;
        arrow->y += MENU_SPACE_BETWEEN_BUTTONS;
    }
}
