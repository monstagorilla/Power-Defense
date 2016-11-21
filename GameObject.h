#pragma once

#include "Point.h"
#include "Sprite.h"

#include <vector>

class GameObject {
public:
    GameObject();
    GameObject(const Point pos);
    virtual ~GameObject();

    virtual void update();
    virtual void draw();

    Point pos;
    std::vector<Sprite> sprites;
    int ID;
    bool dead;
};
