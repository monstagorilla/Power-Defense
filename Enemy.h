#pragma once

class Shot;
class Map;
class Point;
class Tower;

#include <SDL2/SDL.h>
#include <vector>

#include "GameObject.h"

class Enemy : public GameObject {
public:
    Enemy(Map &map, int health, float speed);
    virtual ~Enemy();

    virtual void update();
    void drawHealthbar(int width = 40, int height = 8, int border = 2);
    void hit(Tower &source, int damage);

    std::vector<SDL_Texture *> textures;
    std::vector<Shot *> shots;
    int loot;

private:
    int maxHealth;
    int health;
    float speed;
    std::vector<Point>::size_type pathIndex;
    Map &map;

    void die();
};
