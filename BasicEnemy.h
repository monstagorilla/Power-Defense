#pragma once

#include "Enemy.h"

class BasicEnemy : public Enemy {
public:
    BasicEnemy(Map &map, const int level);
    virtual ~BasicEnemy();

    virtual void update();
};