#pragma once

#include <string>

#include "GUIObject.h"

class Point;

class Label: public GUIObject{
public:
    Label(const eGUI identifier, const std::string text, const GridPoint pos, const int w, const int h, const SDL_Color color,  void (*functptr)(),const bool isActivated = false, const bool renderInMap = false, const bool leftAligned = true); //never used TODO: implement alignment
    virtual ~Label();

    virtual void draw();
private:
    bool leftAligned;
};