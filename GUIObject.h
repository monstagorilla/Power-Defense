#pragma once

#include <SDL2/SDL.h>

#include "Point.h"
#include <string>
#include <vector>

enum state {
    unfocused = 0,
    focused = 1,
    pressed = 2
};

class GUIObject{
public:
	virtual void draw();
	GUIObject();
	virtual ~GUIObject(){};

	GridPoint pos;
	int width;
	int height;
	bool isActivated;
	std::string text;
	SDL_Color color;
    int state;

	std::vector<GUIObject *> children;

    bool contains(GridPoint p);
};
