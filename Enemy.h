#pragma once

#include <vector>

#include "GameObject.h"
#include "Tower.h"
#include "util.h"
#include "Point.h"

class Enemy : public virtual GameObject {
public:
    Enemy(std::vector<Point> path, int health, float speed);
    virtual ~Enemy();

    virtual void update();
    void hit(Tower& source, int damage);

private:
    int maxHealth;
    int health;
    float speed;
    std::vector<Point> path;
    std::vector<Point>::size_type pathIndex;
};
