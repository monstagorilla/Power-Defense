#pragma once

class TeslaGround;

#include "Tower.h"

class TeslaCoil: public Tower{
public:
    TeslaCoil(const GridPoint pos);
    virtual ~TeslaCoil();

    virtual void update();
    virtual void shoot(TeslaGround* target);
    virtual TowerStats getStats();
    virtual TowerStats getStatsPrev();
    virtual int getMaxUpgrade();

    const static std::vector<TowerStats> stat;
};