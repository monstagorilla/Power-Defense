#pragma once

#include<vector>

#include "Point.h"
#include "Sprite.h"

class GameObject{
public:
    virtual void update() = 0;
    virtual ~GameObject(){};
    Point pos;
    std::vector<Sprite> sprites;
	int ID;
	bool dead = false;
};
