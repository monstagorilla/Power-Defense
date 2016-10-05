#pragma once

#include "GUIObject.h"


enum state {
	unfocused = 0,
	focused = 1,
	pressed = 2
};

class Button : public GUIObject {
public:
	Button(std::string text, int x, int y, int w, int h, const SDL_Color color, const SDL_Color colorPressed);

	~Button();

	virtual void draw();

	SDL_Color colorPressed;
	int state;
};