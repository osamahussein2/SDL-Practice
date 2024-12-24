#pragma once

#include <SDL.h>
#include "Vector2.h"

// This will make the rectangle collision bounds slightly smaller
const static int buffer = 4;

static bool RectangleCollision(SDL_Rect* rect1_, SDL_Rect* rect2_)
{
	int rect1HBuf = rect1_->h / buffer;
	int rect1WBuf = rect1_->w / buffer;

	int rect2HBuf = rect2_->h / buffer;
	int rect2WBuf = rect2_->w / buffer;

	// If the bottom of Rect1 is less than the top of Rect2 - no collision occured
	if ((rect1_->y + rect1_->h) - rect1HBuf <= rect2_->y + rect2HBuf) { return false; }

	// If the top of Rect1 is more than the bottom of Rect2 - no collision occured
	if (rect1_->y + rect1HBuf >= (rect2_->y + rect2_->h) - rect2HBuf) { return false; }

	// If the right of Rect1 is less than the left of Rect2 - no collision occured
	if ((rect1_->x + rect1_->w) - rect1WBuf <= rect2_->w + rect2WBuf) { return false; }

	// If the left of Rect1 is more than the right of Rect2 - no collision occured
	if (rect1_->x + rect1WBuf >= (rect2_->x + rect2_->w) - rect2WBuf) { return false; }

	// Otherwise, collision occured
	return true;
}