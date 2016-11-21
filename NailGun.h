#pragma once

#include "Tower.h"

class NailGun :public Tower{
public:
    NailGun(const GridPoint pos);
    ~NailGun();

    virtual void update();
    virtual void shoot(Enemy * target, const float angle);
    virtual TowerStats getStats();
    virtual int getMaxUpgrade();

    const static std::vector<TowerStats> stat;
};