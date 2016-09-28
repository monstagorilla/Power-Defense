#pragma once

#include <math.h>
#include <iostream>
#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Point.h"

extern SDL_Renderer *renderer;

static float distance(const Point a, const Point b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
