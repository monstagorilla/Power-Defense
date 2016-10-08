#pragma once

#include "Tower.h"

class BasicTower: public Tower{
	public:	
	BasicTower(const int x, const int y);
	~BasicTower();
	
	virtual void shoot (Enemy* target);
	virtual void update();	
};
