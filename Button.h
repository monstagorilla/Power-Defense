#pragma once

#include "GUIObject.h"

class Button : public GUIObject {
public:
	Button(std::string text, int x, int y, int w, int h, const SDL_Color color, const SDL_Color colorPressed, void (*onClick)());

	~Button();

	virtual void draw();

	SDL_Color colorPressed;
};