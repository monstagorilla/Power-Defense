#pragma once

#include <vector>

#include "GameObject.h"
#include "util.h"

class Enemy : GameObject {
public:
    Enemy();
    virtual ~Enemy();

    virtual void update();

private:
    int maxHealth;
    int Health;
    float speed;
    std::vector<Point> path;
    std::vector<Point>::size_type pathIndex;
};
