#pragma once

#include "Tower.h"

class BasicTower: public Tower{
	public:	
	BasicTower(const GridPoint pos);
	virtual ~BasicTower();
	
	virtual void shoot (Enemy* target);
	virtual void update();	
};
