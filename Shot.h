#pragma once

#include "GameObject.h"

class Shot: public GameObject{
public:
	Shot(const int x, const int y, const int direction);
	~Shot();

	virtual void update();

	int direction;
	int speed;

};