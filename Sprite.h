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
	Sprite(SDL_Renderer* renderer);
	virtual ~Sprite();
	
	virtual void draw();
	virtual void loadImage(string path);
	
	SDL_Texture* texture;
	SDL_Renderer* renderer; 
	Point pos;
	int width;
	int height;

	float rotation;
	float scale;
};
