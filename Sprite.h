#pragma once

#include <vector>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <iostream>

#include "Point.h"
#include "util.h"

using namespace std;

class Sprite{
	public:
	Sprite();
	Sprite(const SDL_Renderer* renderer)
	virtual ~Sprite(const string path);
	
	virtual void draw();
	virtual void loadImage(const string path);
	
	SDL_Texture* image;
	SDL_Renderer* renderer; 
	Point pos; 
	float rotation;
	float scale;
};
