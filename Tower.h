#pragma once

class Enemy;
class GridPoint;

#include <string>
#include <vector>

#include "GameObject.h"
#include "config.h"

struct Stats {
    int reloadTime = 0;
    float range = 0;
    int price =0;
    int damage =0;
    std::vector<std::string> paths;
};

class Tower : public GameObject {
public:
    Tower();

    Tower(const GridPoint pos);

    virtual ~Tower();

    virtual void update();

    virtual void shoot(Enemy *target);

    virtual Stats getStats();

    virtual int getMaxUpgrade();

    const static std::vector<Stats> stat;
    int currentUpgrade;
    float rotation;
    int cooldown;
};
