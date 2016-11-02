#pragma once

#include "GameObject.h"

class Tower;
class Point;
class Enemy;

class Shot: public GameObject{
public:
	Shot(Point pos, Tower* Parent, Enemy* target, const int damage);
	virtual ~Shot();

	virtual void update();
	void explode();

	Enemy* target;
	Tower* parent;
	float speed;
	int damage;
};
