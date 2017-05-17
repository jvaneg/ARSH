/*
Names: 	Joel v
		Kieran K

Module: Renderer 

Purpose: The renderer module is used for drawing each object of the game to the screen,
		based off of the various positions, values and states of each object.

Details: The renderer heavily invokes calls from the raster module. The screen base must also
		be a pointer to a monochrome 640x400 resolution screen.
*/

#ifndef RENDERER_H
#define RENDERER_H

#include "types.h"
#include "model.h"
#include "raster.h"
#include "clear_qk.h"
#include "ikbd.h"
#include <stdlib.h>

#define TUMBLEWEED_HEIGHT 64
#define CLOUD_HEIGHT 45

void renderFull(const struct Model *model, UINT32* base);
void renderUpdate(const struct Model *model, UINT32* base);
void renderArsh(const struct Arsh *arsh, UINT32 *base);
void renderObstacle(const struct Obstacle *obstacle, UINT32 *base);
void renderScoreBox(const struct ScoreBox *scoreBox, UINT32 *base);
void renderScore(const struct Score *score, UINT8 *base); 
void renderTumbleweed(const struct Tumbleweed *weed, UINT32* base);
void renderCloud(const struct Cloud *cloud, UINT32 *base);
void renderBackground(const struct Background* bg, UINT32* base);

void renderMenuFull(const struct MenuModel *menu, UINT32* base);
void renderMenuUpdate(const struct MenuModel *menu, UINT32* base);
void renderMenuArrow(const struct SelectArrow *arrow, UINT8* base);
void renderMenuMouse(UINT8* base, int mouseX, int mouseY);
void renderEndMouse(UINT8* base, int mouseX, int mouseY);

void renderEndscreenFull(const struct EndscreenModel* endscreen, UINT32* base);
void renderEndscreenUpdate(const struct EndscreenModel* endscreen, UINT32* base);

void renderPaul(UINT32* base);
void renderAllPauls(UINT32* base);

#endif