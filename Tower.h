#pragma once
#include "GameObject.h"
#include "Enemy.h"
#include "config.h"

class Enemy;
class Shot;

class Tower: public GameObject{
	public:
	Tower();
	Tower(const int x, const int y);
	~Tower();

	virtual void update();
	virtual void shoot(Enemy* target);

	static std::vector<SDL_Texture*> textures;
	float rotation;
	int reload_time;
	int cooldown;
	float range;
	int price;
};
