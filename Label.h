#pragma once

#include "GUIObject.h"

#include <string>

class Point;

class Label: public GUIObject{
public:
    Label(const std::string text, const GridPoint pos, int w, int h, const SDL_Color color,  void (*functptr)());
    virtual ~Label();

    virtual void draw();
};