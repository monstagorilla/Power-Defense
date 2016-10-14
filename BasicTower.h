#pragma once

#include "Tower.h"

class BasicTower: public Tower{
	public:	
	BasicTower(const GridPoint pos);
	virtual ~BasicTower();

	virtual void shoot (Enemy* target);
	virtual void update();
	virtual stats getStats();
	virtual int getMaxUpgrade();

	const static std::vector<stats> stat;
};
