#pragma once

#include "GUIObject.h"

class Container : public GUIObject{
public:
    Container(const eGUI identifier);
    virtual ~Container();

    virtual void update();
    virtual void draw();
};