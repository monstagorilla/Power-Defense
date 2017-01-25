#pragma once

class Shot;
class Map;
class Point;
class Tower;

#include <SDL2/SDL.h>
#include <vector>

#include "GameObject.h"

struct EnemyStats{
    int maxHealth;
    float speed;
    int loot;
};

class Enemy : public GameObject {
public:
    virtual ~Enemy();

    virtual void update();
    virtual void draw();

    EnemyStats getStat();
    void drawHealthbar(int width = 40, int height = 8, int border = 2);
    void hit(Tower &source, int damage);

    std::vector<SDL_Texture *> textures;
    std::vector<Shot *> shots;
    int level;

protected:
    void die();

    Enemy(Map &map,const int level, const int health,const float speed, const int loot, const std::string spritePath);
    Map &map;
    std::vector<Point>::size_type pathIndex;

private:
    EnemyStats stat;

    int health;
};
