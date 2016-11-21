#pragma once

class GridPoint;
class Enemy;

#include "Tower.h"

class BasicTower : public Tower {
public:
    BasicTower(const GridPoint pos);
    virtual ~BasicTower();

    virtual void shoot(Enemy *target, const float angle);
    virtual void update();
    virtual TowerStats getStats();
    virtual int getMaxUpgrade();

    const static std::vector<TowerStats> stat;
};
