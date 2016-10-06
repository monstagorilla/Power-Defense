#pragma once

#include <vector>

#include "GameObject.h"
#include "Tower.h"
#include "Shot.h"
#include "util.h"
#include "Point.h"
#include "Map.h"

class Tower;
class Shot;

class Enemy : public GameObject {
public:
    Enemy(Map& map, int health, float speed);
    virtual ~Enemy();

    virtual void update();
    void hit(Tower& source, int damage);
    std::vector<SDL_Texture*> textures;
	std::vector<Shot*> shots;

private:
    int maxHealth;
    int health;
    float speed;
    std::vector<Point>::size_type pathIndex;
    Map &map;

	void die();
};
