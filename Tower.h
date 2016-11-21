#pragma once

class Enemy;
class GridPoint;

#include <string>
#include <vector>

#include "GameObject.h"

struct TowerStats {
    int reloadTime = 0;
    float range = 0;
    int price =0;
    int damage =0;
    std::vector<std::string> paths;
};

class Tower : public GameObject {
public:
    Tower();

    Tower(const GridPoint pos, const std::vector<std::string> paths);

    virtual ~Tower();

    virtual void update();

    virtual void shoot(Enemy *target);

    virtual TowerStats getStats();

    virtual int getMaxUpgrade();

    const static std::vector<TowerStats> stat;
    int currentUpgrade;
    float rotation;
    int cooldown;
};
