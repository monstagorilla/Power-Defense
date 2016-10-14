#pragma once

#include "GUIObject.h"

#include <string>

class Label: public GUIObject{
public:
    Label(const std::string text, int x, int y, int w, int h, const SDL_Color color, void (*funcptr)());
    ~Label();

    virtual void draw();
};