#include "GameObject.h"
#include "Tower.h"
#include "Shot.h"
#include "util.h"
#include "globals.h"

#include <math.h>

extern SDL_Renderer *renderer;

Tower::Tower(const int x, const int y) {
	pos.x = (x + 0.5f) * TILE_WIDTH;
	pos.y = (y + 0.5f) * TILE_HEIGHT;
	//sprites
	rotation = 0;
	reload_time = 20;
	cooldown = 0;
	range = 100;
	price = 100;
	ID = 2;
	for (std::string path : {"/assets/TowerBase.png", "/assets/TowerTurret.png"}) {
		sprites.push_back(Sprite( pos.x, pos.y, TILE_WIDTH, TILE_HEIGHT, path));
	}
}

Tower::~Tower() {

}

void Tower::update() {
	Enemy *nearest;
	auto shortestDist = range;
	for (int i = 0; i < allGameObjects.size(); i++) {
		if (allGameObjects[i]->ID == 1 &&
				distance(allGameObjects[i]->pos, this->pos) <
				shortestDist) {
			nearest = (Enemy *) allGameObjects[i];
			shortestDist = distance(allGameObjects[i]->pos, this->pos);
		}
	}
	if (shortestDist < range) {
		rotation = atan2(nearest->pos.y - this->pos.y,
						 nearest->pos.x - this->pos.x) * 180.0 /
				   M_PI + 90;
		sprites[1].rotation = rotation;
		if (cooldown <= 0){
			shoot(nearest);
			cooldown = reload_time;
		}
	}
	cooldown -= 1;
}

void Tower::shoot(Enemy* target) {
	allGameObjects.push_back(new Shot(pos, this, target));
}
