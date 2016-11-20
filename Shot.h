#pragma once

#include "GameObject.h"

class Tower;

class Point;

class Enemy;

class Shot : public GameObject {
public:
    Shot(const Point pos, Tower *Parent, Enemy *target, const int damage, const float angle);
    virtual ~Shot();

    virtual void update();

    Enemy *target;
    Tower *parent;
    int damage;

private:
    float angle;
};
