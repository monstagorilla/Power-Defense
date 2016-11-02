#pragma once

#include "GUIObject.h"

class Point;

class MapOverlay : public GUIObject{
public:
    MapOverlay(const Point pos, const int width, const int height, void(*onClick)());
    virtual ~MapOverlay();

    virtual void draw();
    virtual void update();

    void(*onCLick)();
};