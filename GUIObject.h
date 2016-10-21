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
	GUIObject();
	virtual ~GUIObject(){};

    virtual void update();
    virtual void draw();
    GUIObject *getChild(const std::string path);
    std::vector<GUIObject*> traverse();

	Point pos;
	int width;
	int height;

	bool isActivated;
	std::string text;
	SDL_Color color;
    int state;
    void (*onClick)();
    std::vector<GUIObject *> children;

    bool contains(GridPoint p);
};
