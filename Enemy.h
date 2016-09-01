#pragma once

#include <vector>

#include "util.h"

class Enemy : GameObject {
public:
    Enemy();
    virtual ~Enemy();

private:
    int maxHealth;
    int Health;
    float speed;
    std::vector<Point> path;
    std::vector<T>::size_type pathIndex;
}
