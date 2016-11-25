#pragma once

class Point;

#include "Shot.h"

class Grenade : public Shot{
public:
    Grenade(const Point pos, Tower *parent, Enemy *target, const int damage, const float angle, const float speed);
    virtual ~Grenade();

    virtual void update();
    virtual void explode();

private:
    float explosionRad;
    Point destPos;
};