#pragma once

#include "GameObject.h"

class Tower;

class Point;

class Enemy;

class Shot : public GameObject {
public:
    Shot(const Point pos, Tower *Parent, Enemy *target, const int damage, const float angle, const int speed);
    virtual ~Shot();

    virtual void update();
    virtual void explode();

    Enemy *target;
    Tower *parent;
    int damage;

protected:
    void turnTowards(const Point target, const float turnAngle);
    float angle;
    float speed;
};
