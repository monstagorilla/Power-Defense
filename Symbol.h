#pragma once

#include <vector>
#include <string>

class Sprite;
class GridPoint;

#include "GUIObject.h"

class Symbol: public GUIObject{
public:
    Symbol(std::vector<std::string> paths, GridPoint pos);
    virtual ~Symbol();

    virtual void update();
    virtual void draw();

private:
    std::vector<Sprite> sprites;
};