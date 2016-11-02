#pragma once

#include "GUIObject.h"

class GridPoint;

class Button : public GUIObject {
public:
    Button(const std::string text, const GridPoint pos, const int w, const int h, const SDL_Color color,
           const SDL_Color colorPressed, void (*onCLick)());
    ~Button();

    virtual void draw();
    virtual void update();

    SDL_Color colorPressed;
};