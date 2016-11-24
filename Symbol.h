#pragma once

#include <vector>
#include <string>

class Sprite;
class GridPoint;

#include "GUIObject.h"

class Symbol: public GUIObject{
public:
    Symbol(const bool isTransparent);
    Symbol(const std::vector<std::string> paths, const GridPoint pos, void (*onCLick)());
    virtual ~Symbol();

    virtual void update();
    virtual void draw();

    std::vector<Sprite> sprites;
private:
    bool isTransparent;
};