#pragma once

#include "GUIObject.h"
#include "Point.h"

#include <string>

class Label: public GUIObject{
public:
    Label(const std::string text, const GridPoint pos, int w, int h, const SDL_Color color,  void (*functptr)());
    virtual ~Label();

    virtual void draw();
};