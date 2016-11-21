#pragma once

#include "GUIObject.h"

class Container : public GUIObject{
public:
    Container();
    virtual ~Container();

    virtual void update();
    virtual void draw();
};