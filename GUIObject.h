#pragma once

#include <SDL2/SDL.h>

#include "Point.h"
#include <string>
#include <vector>

class GUIObject{
public:
	virtual void draw() = 0;
	void setIsActivated(const bool state){
		isActivated = state;
	}

	Point pos;
	int width;
	int height;
	bool isActivated;
	std::string text;
	SDL_Color color;
	std::vector<GUIObject> children;
};