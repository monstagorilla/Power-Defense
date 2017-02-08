#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <vector>

#include "Point.h"
#include "enumGUI.h"

enum state {
    unfocused = 0,
    focused = 1,
    pressed = 2
};

class GUIObject{
public:
	GUIObject(const eGUI identifier, const bool renderInMap = false);
	virtual ~GUIObject();

    virtual void update();
    virtual void draw();
    GUIObject *getChild(const eGUI identifier);
    std::vector<GUIObject*> traverse();

	eGUI identifier;
	Point pos;
	int width;
	int height;

	bool isActivated;
	std::string text;
	SDL_Color color;
    int state;
    void (*onClick)();
    std::vector<GUIObject *> children;

protected:
	bool renderInMap;
};
