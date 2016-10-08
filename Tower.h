#pragma once

#include "GameObject.h"
#include "Enemy.h"
#include "config.h"


class Enemy;
class Shot;

struct stats {
	int reloadTime;
	float range;
	int price;
	std::vector<std::string> paths;
};

class Tower: public GameObject{
	public:
	Tower(){};
	Tower(const int x, const int y);
	~Tower();

	virtual void update(){};
	virtual void shoot(Enemy* target){};
	stats getStats();

	const static std::vector<stats> stat;

	int currentUpgrade;
	float rotation;
	int cooldown;
};
