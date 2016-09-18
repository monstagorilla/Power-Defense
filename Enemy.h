#pragma once

#include <vector>

#include "GameObject.h"
#include "Tower.h"
#include "util.h"
#include "Point.h"
#include "Map.h"

class Enemy : public GameObject {
public:
    Enemy(Map& map, int health, float speed, SDL_Renderer* renderer);
    virtual ~Enemy();

    virtual void update();
    void hit(Tower& source, int damage);
    SDL_Renderer* renderer;

private:
    int maxHealth;
    int health;
    float speed;
    std::vector<Point>::size_type pathIndex;
    Map &map;
};
