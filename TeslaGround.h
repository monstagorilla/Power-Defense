#pragma once

#include "Tower.h"

class TeslaGround: public Tower {
public:
    TeslaGround(const GridPoint pos);
    virtual ~TeslaGround();


    virtual void shoot();
    virtual void update();

    virtual TowerStats getStats();
    virtual TowerStats getStatsPrev();
    virtual int getMaxUpgrade();

    const static std::vector<TowerStats> stat;
};