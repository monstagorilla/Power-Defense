#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <vector>

#include "Point.h"

enum state {
    unfocused = 0,
    focused = 1,
    pressed = 2
};

class GUIObject{
public:
	GUIObject(const bool renderInMap = false);
	virtual ~GUIObject();

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
protected:
	bool renderInMap;
};
