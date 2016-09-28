#include "GameObject.h"
#include "Tower.h"
#include "Enemy.h"
#include "util.h"

#include <math.h>
#include <typeinfo>

extern SDL_Renderer *renderer;

Tower::Tower(const int x, const int y) {
	pos.x = x;
	pos.y = y;
	//sprites
	rotation = 0;
	cooldown = 2;
	range = 300;
	price = 100;
	ID = 2;
	for (std::string path : {"/assets/TowerBase.png", "/assets/TowerTurret.png"}) {
		this->sprites.push_back(Sprite(pos.x, pos.y, TILE_WIDTH, TILE_WIDTH, path));
	}
}

Tower::~Tower() {

}

void Tower::update() {
	extern std::vector<GameObject *> allGameObjects;
	Enemy *nearest;
	int shortestDist = range;
	for (int i = 0; i < allGameObjects.size(); i++) {
		if (allGameObjects[i]->ID == 1 && distance(allGameObjects[i]->pos, this->pos) < shortestDist) {
			nearest = (Enemy *) allGameObjects[i];
			shortestDist = distance(allGameObjects[i]->pos, this->pos);
		}
	}
	if (shortestDist < range) {
		rotation = atan2(nearest->pos.y - this->pos.y, nearest->pos.x - this->pos.x) * 360 /
				   (2.0 * 3.14159265358979323846) + 90;
		sprites[1].rotation = rotation;
	}
}

void Tower::shoot() {

}
