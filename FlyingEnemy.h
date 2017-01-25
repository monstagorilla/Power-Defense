#pragma once

#include "Enemy.h"

class FlyingEnemy: public Enemy{
public:
    FlyingEnemy(Map &map, const int level, const Point pos);
    virtual ~FlyingEnemy();

    virtual void update();
};