#include "GameObject.h"
#include "Tower.h"
#include "Enemy.h"
#include "util.h"
#include "globals.h"

#include <math.h>

extern SDL_Renderer *renderer;

Tower::Tower(const int x, const int y) {
	pos.x = x;
	pos.y = y;
	//sprites
	rotation = 0;
	cooldown = 2;
	range = 100;
	price = 100;
	ID = 2;
	for (std::string path : {"/assets/TowerBase.png", "/assets/TowerTurret.png"}) {
		sprites.push_back(Sprite( (pos.x + 0.5f) * TILE_WIDTH,  (pos.y + 0.5f) * TILE_HEIGHT,
								 TILE_WIDTH, TILE_HEIGHT, path));
	}
}

Tower::~Tower() {

}

void Tower::update() {
	Enemy *nearest;
	auto shortestDist = range;
	for (int i = 0; i < allGameObjects.size(); i++) {
		if (allGameObjects[i]->ID == 1 &&
			distance(allGameObjects[i]->pos, {(this->pos.x + 0.5f) * TILE_WIDTH, (this->pos.y + 0.5f) * TILE_HEIGHT}) <
			shortestDist) {
			nearest = (Enemy *) allGameObjects[i];
			shortestDist = distance(allGameObjects[i]->pos,
									{(this->pos.x + 0.5f) * TILE_WIDTH, (this->pos.y + 0.5f) * TILE_HEIGHT});
		}
	}
	if (shortestDist < range) {
		rotation = atan2(nearest->pos.y - (this->pos.y + 0.5f) * TILE_HEIGHT,
						 nearest->pos.x - (this->pos.x + 0.5f) * TILE_WIDTH) * 180.0 /
				   M_PI + 90;
		sprites[1].rotation = rotation;
	}
}

void Tower::shoot() {

}
