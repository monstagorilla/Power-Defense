#pragma once

class GridPoint;
class Enemy;

#include "Tower.h"

class BasicTower : public Tower {
public:
    BasicTower(const GridPoint pos);
    virtual ~BasicTower();

    virtual void shoot(Enemy *target);
    virtual void update();
    virtual Stats getStats();
    virtual int getMaxUpgrade();

    const static std::vector<Stats> stat;
};
