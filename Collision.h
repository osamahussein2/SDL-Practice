#pragma once

#include <SDL.h>
#include "Vector2.h"

// This will make the rectangle collision bounds slightly smaller
const static int buffer = 4;

static bool RectangleCollision(SDL_Rect* rect1_, SDL_Rect* rect2_)
{
    int aHBuf = rect1_->h / buffer;
    int aWBuf = rect1_->w / buffer;

    int bHBuf = rect2_->h / buffer;
    int bWBuf = rect2_->w / buffer;

    // If the bottom of A is less than the top of B - no collision
    if ((rect1_->y + rect1_->h) - aHBuf <= rect2_->y + bHBuf) { return false; }

    // If the top of A is more than the bottom of B = no collision
    if (rect1_->y + aHBuf >= (rect2_->y + rect2_->h) - bHBuf) { return false; }

    // If the right of A is less than the left of B - no collision
    if ((rect1_->x + rect1_->w) - aWBuf <= rect2_->x + bWBuf) { return false; }

    // If the left of A is more than the right of B - no collision
    if (rect1_->x + aWBuf >= (rect2_->x + rect2_->w) - bWBuf) { return false; }

	// Otherwise, collision occured
	return true;
}