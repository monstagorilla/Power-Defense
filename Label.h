#pragma once

#include <string>

#include "GUIObject.h"

class Point;

class Label: public GUIObject{
public:
    Label(const std::string text, const GridPoint pos, const int w, const int h, const SDL_Color color,  void (*functptr)(),const bool isActivated = false, const bool leftAligned = true );
    virtual ~Label();

    virtual void draw();
private:
    bool leftAligned;
};