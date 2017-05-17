/*
Name:   Joel v
        Kieran K

Module: Deputy Arsh
*/

#include "dep_arsh.h"


/* Globals required for VBL ISR */
UINT8 renderRequest = FALSE; /* whether or not a render request has been set by the ISR */
UINT8 gameState = NO_GAME;   /* whether we are currently at the main menu, playing the game, or at the endscreen */

UINT8 globalTimeCounter = 0;   /* the time counter being used in the main game loop */
UINT8 oldSpawnRate;      /* the previous obstacle spawnRate to determine if the spawnRate has changed */

struct Model gameWorld = /* the main game model, global so the ISR can access it */
{
    /* ARSH */
    {
        ARSH_STANDARD_LEFT, ARSH_STANDARD_TOP, 
        ARSH_STANDARD_RIGHT, ARSH_STANDARD_BOTTOM,
        ARSH_STANDARD_LEFT,
        0,
        0,
        run,
        TRUE,
        1
    },
    /* OBSTACLES */
    {
     {
        bale, 
        OBSTACLE_DEACTIVATED_LEFT, OBSTACLE_DEACTIVATED_TOP,
        OBSTACLE_DEACTIVATED_LEFT, OBSTACLE_DEACTIVATED_TOP,
        OBSTACLE_VELOCITY,
        FALSE,
        FALSE,
        FALSE
     },
     {
        bale, 
        OBSTACLE_DEACTIVATED_LEFT, OBSTACLE_DEACTIVATED_TOP,
        OBSTACLE_DEACTIVATED_LEFT, OBSTACLE_DEACTIVATED_TOP,
        OBSTACLE_VELOCITY,
        FALSE,
        FALSE,
        FALSE
     }
    },
    /* SCOREBOX */
    {
        SCOREBOX_LEFT, SCOREBOX_TOP
    },
    /* SCORE */  
    {
        SCOREBOX_SCORE_LEFT, SCOREBOX_TOP+3,
        0
    },
    /* WEED */
    {
        OBSTACLE_DEACTIVATED_LEFT, OBSTACLE_BALE_TOP,
        OBSTACLE_VELOCITY + 3,
        TRUE
    },
    /* CLOUD */
    {
        OBSTACLE_DEACTIVATED_LEFT, CLOUD_TOP,
        OBSTACLE_VELOCITY
    },
    /* BACKGROUND */
    {
        BG_SUN_LEFT, BG_SUN_TOP,
        BG_STAGE_TOP,
        BG_STAGE_HEIGHT
    },
    /* MUSIC */
    {
        0,
        FALSE
    },
    /* STARTING SPAWNRATE */
    OBSTACLE_START_SPAWNRATE,
    /* STARTING OBSTACLE SPEED */
    OBSTACLE_VELOCITY
};

struct Model defaultWorld = /* a default game world state for quick resets with memcpy */
{
    /* ARSH */
    {
        ARSH_STANDARD_LEFT, ARSH_STANDARD_TOP, 
        ARSH_STANDARD_RIGHT, ARSH_STANDARD_BOTTOM,
        ARSH_STANDARD_LEFT,
        0,
        0,
        run,
        TRUE,
        1
    },
    /* OBSTACLES */
    {
     {
        bale, 
        OBSTACLE_DEACTIVATED_LEFT, OBSTACLE_DEACTIVATED_TOP,
        OBSTACLE_DEACTIVATED_LEFT, OBSTACLE_DEACTIVATED_TOP,
        OBSTACLE_VELOCITY,
        FALSE,
        FALSE,
        FALSE
     },
     {
        bale, 
        OBSTACLE_DEACTIVATED_LEFT, OBSTACLE_DEACTIVATED_TOP,
        OBSTACLE_DEACTIVATED_LEFT, OBSTACLE_DEACTIVATED_TOP,
        OBSTACLE_VELOCITY,
        FALSE,
        FALSE,
        FALSE
     }
    },
    /* SCOREBOX */
    {
        SCOREBOX_LEFT, SCOREBOX_TOP
    },
    /* SCORE */  
    {
        SCOREBOX_SCORE_LEFT, SCOREBOX_TOP+3,
        0
    },
    /* WEED */
    {
        OBSTACLE_DEACTIVATED_LEFT, OBSTACLE_BALE_TOP,
        OBSTACLE_VELOCITY + 3,
        TRUE
    },
    /* CLOUD */
    {
        OBSTACLE_DEACTIVATED_LEFT, CLOUD_TOP,
        OBSTACLE_VELOCITY
    },
    /* BACKGROUND */
    {
        BG_SUN_LEFT, BG_SUN_TOP,
        BG_STAGE_TOP,
        BG_STAGE_HEIGHT
    },
    /* MUSIC */
    {
        0,
        FALSE
    },
    /* STARTING SPAWNRATE */
    OBSTACLE_START_SPAWNRATE,
    /* STARTING OBSTACLE SPEED */
    OBSTACLE_VELOCITY
};


struct MenuModel menu = /* structure for the menu, global so it can be accessed by the vbl isr */
{
    /* BUTTONS */
    {
        /* ONE PLAYER BUTTON */
        {
            ONEPLAYER_LEFT, ONEPLAYER_TOP,
            ONEPLAYER_RIGHT, ONEPLAYER_BOTTOM
        },
        /* TWO PLAYER BUTTON */
        {
            TWOPLAYER_LEFT, TWOPLAYER_TOP,
            TWOPLAYER_RIGHT, TWOPLAYER_BOTTOM
        },
        /* QUIT BUTTON */
        {
            QUIT_LEFT, QUIT_TOP,
            QUIT_RIGHT, QUIT_BOTTOM
        }
    },
    /* SELECTION ARROW */  
    {
        ONEPLAYER_LEFT - 12, ONEPLAYER_TOP + 1,
        0
    },
    /* MOUSE X */
    0,
    /* MOUSE Y */
    0,
    /* OLD MOUSE X */
    -100,
    /* OLD MOUSE Y */
    -100
};
    
    
struct EndscreenModel endscreen = /* structure for endscreen, global to be available to isr */
{
    /* BUTTONS */
    {
        /* MAIN MENU BUTTON */
        {
            MAIN_LEFT, MAIN_TOP,
            MAIN_RIGHT, MAIN_BOTTOM
        },
        /* QUIT BUTTON */
        {
            QUIT_LEFT, QUIT_TOP,
            QUIT_RIGHT, QUIT_BOTTOM
        }
    },
    /* SELECTION ARROW */  
    {
        MAIN_LEFT - 12, MAIN_TOP + 1,
        0
    },
    /* SCORE */  
    {
        END_SCORE_LEFT, END_SCORE_TOP,
        0
    },
    /* MOUSE X */
    0,
    /* MOUSE Y */
    0,
    /* OLD MOUSE X */
    -100,
    /* OLD MOUSE Y */
    -100
};




/* Alternate buffer for double buffering */
UINT8 altBuffer[32255];


/*
Name: main
Purpose: controls flowing between menus and the game
*/
int main()
{   
    int mainSelection = -1;
    int endSelection = -1;
    int finalScore = -1;

    void* mainBase = getVideoBase();
    void* altBase = NULL;
    
    UINT8 altBufferStart;
    Vector origIKBD = installVector(IKBD_ISR, ikbdisr); /* installs the custom ikbd isr */
    Vector origVBL = installVector(VBL_ISR, vblisr); /* installs the custom vbl isr */
    
    srand(time(NULL));
    
    altBufferStart = ((UINT8) &altBuffer[0]) % 256;
    if(altBufferStart == 0)
    {
        altBase = &altBuffer[0];
    }
    else
    {
        altBase = &altBuffer[256 - altBufferStart];
    }
    
    
    while( mainSelection != MAIN_QUIT && endSelection != 1)
    {   
        mainSelection = playMenu(mainBase);
        
        switch (mainSelection)
        {
            case MAIN_1P:
                finalScore = playGame(mainBase, altBase);
                
                if( finalScore != -1)
                {
                    endSelection = playEndscreen(mainBase, finalScore);
                }
                else
                {
                    endSelection = 1;
                }
                break;
                
            case MAIN_2P:
                mainSelection = MAIN_QUIT; /* temporary force quit until 2 player is added */
                renderAllPauls(mainBase);
                break;
                
            default:
                break;
        }
    
    }
    
    installVector(IKBD_ISR, origIKBD); /* reinstalls the original ikbd isr*/
    installVector(VBL_ISR, origVBL); /* uninstalls the new vbl isr, puts the old one back */
    
    return 0;
}


/*
Name: playGame

Purpose: Contains the main game loop

Input: mainBase - pointer to the start of the frame buffer, type void*
       altBase - pointer to the start of the alternate frame buffer, type void*
       
Details: See main file documentation from control details
*/
int playGame(void* mainBase, void* altBase)
{   
    UINT8 userQuit;
    char inputChar;
    int finalScore;
    
    void* base;
    UINT8 mainBuffer = FALSE;
    
    memcpy(&gameWorld, &defaultWorld, sizeof(gameWorld));
    
    gameState = PLAYING_GAME;
    globalTimeCounter = 140;
    oldSpawnRate = gameWorld.spawnRate;
    base = mainBase;
    
    initialize_mixer();
    setVideoBase(altBase);
    renderFull(&gameWorld, base);
    renderFull(&gameWorld, altBase);
    userQuit = FALSE;
    
    while(!userQuit && gameWorld.arsh.alive)
    {
        if(inputPending())
        {
            inputChar = (char) readChar();
            
            switch (inputChar)
            {
                case 'z':
                    setArshJump(&gameWorld.arsh);
                    break;
                    
                case 'x':
                    setArshKick(&gameWorld.arsh);
                    break;
                    
                case 'c':
                    setArshSlide(&gameWorld.arsh);
                    break;
                    
                case 'p':
                    swapArshSkin(&gameWorld.arsh);
                    break;
                    
                case 'q':
                    userQuit = TRUE;
                    break;
            }
        }
        
        if(renderRequest)
        {  
            /* Rendering */
            renderUpdate(&gameWorld,base); 
                            
            if( mainBuffer )
            {
                setVideoBase(altBase);
                base = mainBase;
                mainBuffer = FALSE;     
            }
            else
            {
                setVideoBase(mainBase);
                base = altBase;
                mainBuffer = TRUE;  
            }
            
            renderRequest = FALSE;
        }
    }
        
    
    stop_sound();
    /* sets the screen back to the original frame buffer */
    setVideoBase(mainBase);
    
    if( userQuit )
    {
        finalScore = -1;
    }
    else
    {
        finalScore = gameWorld.score.scoreValue;
    }
    
    gameState = NO_GAME;
    
    return finalScore;
}


/*
Name: playMenu

Purpose: Contains the menu "game" loop

Input: mainBase - pointer to the start of the frame buffer, type void*
       
Details: Conceptually is doing the same thing as the main game loop, except the "game"
         is just a simple menu
         
         Controls:
            UP_ARROW - move selection up
            DOWN_ARROW - move selection down
            ENTER - make selection
            Q - quit
*/
int playMenu(void* mainBase)
{
    UINT8 selectionMade;
    UINT8 inputKey;
    int selection = 0;
    UINT8 buttonIndex;       
    UINT8 buttonHovered = FALSE;
    
    void* base;
    
    
    base = mainBase;
    
    setVideoBase(mainBase);
    
    gameState = MAIN_MENU;
 
    menu.mouseX = ikbdBuffer.mouseX;
    menu.mouseY = ikbdBuffer.mouseY;
    renderMenuFull(&menu, base);
    
    selectionMade = FALSE;
    
    while(!selectionMade)
    {
        
        if(inputPending())
        {
            inputKey = readKeyMap();
            
            switch (inputKey)
            {
                case LMB_RMB_CLICK:
                case LMB_CLICK:
                    for(buttonIndex = 0; !buttonHovered && (buttonIndex < MENU_MAX_BUTTONS); buttonIndex++)
                    {
                        if( checkMouseOver(&menu.buttons[buttonIndex], menu.mouseX, menu.mouseY) )
                        {
                            buttonHovered = TRUE;
                            selection = menu.selectArrow.selected;
                            selectionMade = TRUE;
                        }
                    }
                    break;
                
                case KEY_UP:
                    moveSelectionUp(&menu.selectArrow);
                    break;
                    
                case KEY_DOWN:
                    moveSelectionDown(&menu.selectArrow, MENU_MAX_SELECTION);
                    break;
                    
                case KEY_RETURN:
                    selection = menu.selectArrow.selected;
                    selectionMade = TRUE;
                    break;
                    
                case KEY_Q:
                    selection = 2;
                    selectionMade = TRUE;
                    break;
            }
        }

        if(renderRequest)
        {   
            /* Rendering */
            menu.oldMouseX = menu.mouseX;
            menu.oldMouseY = menu.mouseY;
            menu.mouseX = ikbdBuffer.mouseX;
            menu.mouseY = ikbdBuffer.mouseY;
            renderMenuUpdate(&menu,base); 

            renderRequest = FALSE;  
        }
            
    }
    
    gameState = NO_GAME;
    
    return selection;
}


/*
Name: playEndscreen

Purpose: Contains the menu "game" loop

Input: mainBase - pointer to the start of the frame buffer, type void*
       
Details: Conceptually is doing the same thing as the main game loop, except the "game"
         is just a simple menu
         
         Controls:
            UP_ARROW - move selection up
            DOWN_ARROW - move selection down
            ENTER - make selection
            Q - quit
*/
int playEndscreen(void* mainBase, int finalScore)
{
    UINT8 selectionMade;
    UINT8 inputKey;
    int selection = 0;
    UINT8 buttonIndex;       
    UINT8 buttonHovered = FALSE;
    
    void* base;
    
    
    endscreen.finalScore.scoreValue = finalScore;
    
    base = mainBase;
    
    setVideoBase(mainBase);
    
    gameState = END_SCREEN;
    
    endscreen.mouseX = ikbdBuffer.mouseX;
    endscreen.mouseY = ikbdBuffer.mouseY;
    renderEndscreenFull(&endscreen, base);
    
    selectionMade = FALSE;
    
    while(!selectionMade)
    {
        if(inputPending())
        {
            inputKey = readKeyMap();
            
            switch (inputKey)
            {
                case LMB_RMB_CLICK:
                case LMB_CLICK:
                    for(buttonIndex = 0; !buttonHovered && (buttonIndex < ENDSCREEN_MAX_BUTTONS); buttonIndex++)
                    {
                        if( checkMouseOver(&endscreen.buttons[buttonIndex], endscreen.mouseX, endscreen.mouseY) )
                        {
                            buttonHovered = TRUE;
                            selection = endscreen.selectArrow.selected;
                            selectionMade = TRUE;
                        }
                    }
                    break;
                    
                case KEY_UP:
                    moveSelectionUp(&endscreen.selectArrow);
                    break;
                    
                case KEY_DOWN:
                    moveSelectionDown(&endscreen.selectArrow, ENDSCREEN_MAX_SELECTION);
                    break;
                    
                case KEY_RETURN:
                    selection = endscreen.selectArrow.selected;
                    selectionMade = TRUE;
                    break;
                    
                case KEY_Q:
                    selection = 1;
                    selectionMade = TRUE;
                    break;
            }
        }

        if(renderRequest)
        {   
            /* Rendering */
            endscreen.oldMouseX = endscreen.mouseX;
            endscreen.oldMouseY = endscreen.mouseY;
            endscreen.mouseX = ikbdBuffer.mouseX;
            endscreen.mouseY = ikbdBuffer.mouseY;
            renderEndscreenUpdate(&endscreen,base); 

            renderRequest = FALSE;
        }
            
    }
    
    gameState = NO_GAME;
    
    return selection;
}

/*
Name: procSync
Purpose: processes all the synchronous events of the main game loop,
         main menu, or endscreen menu, depending on gameState
Details: This function is meant to be called by the assembly vbl isr
*/
void procSync(void)
{   
    UINT8 obstacleIndex;     /* index of obstacle array */
    UINT8 obstacleFound;     /* whether or not an obstacle has been found */
    UINT8 buttonIndex;       /* index of button array */
    UINT8 buttonHovered;     /* whether or not a button is being hovered */
    
    if(!renderRequest)
    {
        switch(gameState)
        {
            case PLAYING_GAME:
                if(!gameWorld.arsh.alive)
                {
                    /* nothing for now */
                }
                else
                {   
                    updateMusic(&gameWorld.music);
                    switch (gameWorld.arsh.state)
                    {
                        case run:
                            doArshRun(&gameWorld.arsh);
                            break;
                            
                        case jump:
                            doArshJump(&gameWorld.arsh);
                            break;
                            
                        case slide:
                            doArshSlide(&gameWorld.arsh);
                            break;
                            
                        case kick:
                            doArshKick(&gameWorld.arsh);
                            break;
                    }
                    
                    for(obstacleIndex = 0; obstacleIndex < MAX_OBSTACLES; obstacleIndex++)
                    {
                        moveObstacle(&gameWorld.obstacles[obstacleIndex], &gameWorld.score, &gameWorld.spawnRate, &gameWorld.obstacleVelocity);     
                    }
                    
                    if(oldSpawnRate != gameWorld.spawnRate)
                    {
                        globalTimeCounter = 220;
                        oldSpawnRate = gameWorld.spawnRate;
                    }
                    
                    for(obstacleIndex = 0; obstacleIndex < MAX_OBSTACLES; obstacleIndex++)
                    {
                        checkCollision(&gameWorld.arsh, &gameWorld.obstacles[obstacleIndex]);
                    }
                        
                    if(globalTimeCounter == gameWorld.spawnRate)
                    {       
                        obstacleFound = FALSE;
                        for(obstacleIndex = 0; !obstacleFound && (obstacleIndex < MAX_OBSTACLES); obstacleIndex++)
                        {
                            if(!gameWorld.obstacles[obstacleIndex].enabled)
                            {
                                spawnObstacle(&gameWorld.obstacles[obstacleIndex], gameWorld.obstacleVelocity);
                                obstacleFound = TRUE;
                            }
                        }
                        
                        globalTimeCounter = 0;
                    }
                    
                    
                    moveCloud(&gameWorld.cloud);
                    moveTumbleweed(&gameWorld.weed);
                    globalTimeCounter++;
                }
                break;
                
            case MAIN_MENU:
                buttonHovered = FALSE;
                for(buttonIndex = 0; !buttonHovered && (buttonIndex < MENU_MAX_BUTTONS); buttonIndex++)
                {
                    if( checkMouseOver(&menu.buttons[buttonIndex], menu.mouseX, menu.mouseY) )
                    {
                        buttonHovered = TRUE;
                        menu.selectArrow.x = menu.buttons[buttonIndex].x1 - 12;
                        menu.selectArrow.y = menu.buttons[buttonIndex].y1 + 1;
                        menu.selectArrow.selected = buttonIndex;
                    }
                }
                
                break;
            
            case END_SCREEN:
                buttonHovered = FALSE;
                for(buttonIndex = 0; !buttonHovered && (buttonIndex < ENDSCREEN_MAX_BUTTONS); buttonIndex++)
                {
                    if( checkMouseOver(&endscreen.buttons[buttonIndex], endscreen.mouseX, endscreen.mouseY) )
                    {
                        buttonHovered = TRUE;
                        endscreen.selectArrow.x = endscreen.buttons[buttonIndex].x1 - 12;
                        endscreen.selectArrow.y = endscreen.buttons[buttonIndex].y1 + 1;
                        endscreen.selectArrow.selected = buttonIndex;
                    }
                }
                
                break;
                
            default:
                break;
        
        }
        
        renderRequest = TRUE;
    }
    
    return;
}