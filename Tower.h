#pragma once
#include "GameObject.h"
#include "config.h"

class Tower: public GameObject{
	public:
	Tower();
	Tower(const int x, const int y);
	~Tower();

	virtual void update();
	virtual void shoot();

	static std::vector<SDL_Texture*> textures;
	float rotation;
	float cooldown;
	float range;
	int price;
};
