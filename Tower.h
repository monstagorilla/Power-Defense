#pragma once

#include "GameObject.h"
#include "Enemy.h"
#include "config.h"
#include "Point.h"

class Enemy;
class Shot;

struct stats {
	int reloadTime;
	float range;
	int price;
	int damage;
	std::vector<std::string> paths;
};

class Tower: public GameObject{
	public:
	Tower(){};
	Tower(const GridPoint pos);
	virtual ~Tower();

	virtual void update(){};
	virtual void shoot(Enemy* target){};
	virtual stats getStats();
	virtual int getMaxUpgrade();

	const static std::vector<stats> stat;
	int currentUpgrade;
	float rotation;
	int cooldown;

};
