#pragma once
#include "GUIObject.h"

class GridPoint;

class Button : public GUIObject {
public:
	Button(std::string text, const GridPoint pos, int w, int h, const SDL_Color color, const SDL_Color colorPressed, void (*onCLick)());

	~Button();

	virtual void draw();
	virtual void update();

	SDL_Color colorPressed;
};