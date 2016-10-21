#pragma once

#include "GUIObject.h"
#include "Point.h"

class MapOverlay : public GUIObject{
public:
    MapOverlay(const Point pos, const int width, const int height, void(*onClick)());
    virtual ~MapOverlay();

    virtual void draw();
    virtual void update();

    void(*onCLick)();
};