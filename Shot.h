#pragma once

#include "Point.h"
#include "Enemy.h"
#include "Tower.h"
#include "GameObject.h"

class Tower;
class Enemy;

class Shot: public GameObject{
public:
	Shot(Point pos, Tower* Parent, Enemy* target);
	~Shot();

	virtual void update();
	void explode();
	Enemy* target;
	Tower* parent;
	float speed;
	int damage;
};
