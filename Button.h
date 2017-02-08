#pragma once

#include "GUIObject.h"

class GridPoint;

class Button : public GUIObject {
public:
    Button(const eGUI identifier,const std::string text, const GridPoint pos, const int w, const int h, const SDL_Color color,
           const SDL_Color colorPressed, void (*onCLick)(), const bool renderInMap = false);
    virtual ~Button();

    virtual void draw();
    virtual void update();

    SDL_Color colorPressed;
};