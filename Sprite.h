#pragma once

#include <vector>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <iostream>

#include "Point.h"
#include "util.h"

class Sprite{
	public:
	Sprite(){};
	Sprite(const Point pos, const int width, const int height, std::string path);
	virtual ~Sprite();
	
	virtual void draw();

	SDL_Texture* texture;
	Point pos;
	int width;
	int height;

	float rotation;
	float scale;
};
