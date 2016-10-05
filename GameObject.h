#pragma once

#include<vector>

#include "Point.h"
#include "Sprite.h"

class GameObject{
public:
    virtual void update() = 0;

    Point pos;
    std::vector<Sprite> sprites;
	int ID;
};
