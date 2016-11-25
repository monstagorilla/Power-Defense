#pragma once

class Point;
class Tower;
class Enemy;

#include "Shot.h"

class BasicShot: public Shot{
public:
    BasicShot(const Point pos, Tower* parent, Enemy* target, const int damage, const float angle, 
              const int speed, std::string path);
    virtual ~BasicShot();

    virtual void update();
    void explode();

private:
    void turnTowards(const Point target, const float turnAngle);
    float angle;
    float speed;
};
