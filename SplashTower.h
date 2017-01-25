#pragma once

class GridPoint;

#include "Tower.h"

class SplashTower : public Tower{
public:
    SplashTower(const GridPoint pos);
    virtual ~SplashTower();

    virtual void update();
    virtual void shoot(Enemy *target, const float angle);
    virtual TowerStats getStats();
    virtual TowerStats getStatsPrev();
    virtual int getMaxUpgrade();

    const static std::vector<TowerStats> stat;
};