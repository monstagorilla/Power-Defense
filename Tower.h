#pragma once
#include "GameObject.h"
#include "config.h"

class Tower: public GameObject{
	public:
	Tower();
	Tower(const int x, const int y, SDL_Renderer *renderer);
	~Tower();

	virtual void update();
	virtual void shoot();
		
	float rotation;
	float cooldown;
	float range;
	int price;
};
