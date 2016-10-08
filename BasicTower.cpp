#include "BasicTower.h"
#include "globals.h"

const std::vector<stats> Tower::stat=
		{{20, 100, 100, {"/assets/TowerBase.png", "/assets/TowerTurret.png" }},
		 {20, 100, 50,  {"/assets/TowerBase.png", "/assets/TowerTurret1.png"}},
		 {20, 100, 75,  {"/assets/TowerBase.png", "/assets/TowerTurret2.png"}},
		 {15, 125, 100, {"/assets/TowerBase.png", "/assets/TowerTurret3.png"}}};

BasicTower::BasicTower(const int x, const int y) : Tower::Tower(x, y){
	for(auto path: stat[0].paths){
		sprites.push_back(Sprite(pos.x, pos.y, TILE_WIDTH, TILE_HEIGHT, path));
	}
}

BasicTower::~BasicTower(){

}

void BasicTower::shoot(Enemy* target) {
	allGameObjects.push_back(std::make_unique<Shot> (pos, this, target));
}

void BasicTower::update() {
	Enemy *nearest;
	auto shortestDist = getStats().range;
	for (int i = 0; i < allGameObjects.size(); i++) {
		if (allGameObjects[i]->ID == 1 &&
				distance(allGameObjects[i]->pos, this->pos) <
				shortestDist) {
			nearest = (Enemy *) allGameObjects[i].get();
			shortestDist = distance(allGameObjects[i]->pos, this->pos);
		}
	}
	if (shortestDist < getStats().range) {
		rotation = atan2(nearest->pos.y - this->pos.y,
						 nearest->pos.x - this->pos.x) * 180.0 /
				   M_PI + 90;
		sprites[1].rotation = rotation;
		if (cooldown <= 0){
			shoot(nearest);
			cooldown = getStats().reloadTime;
		}
	}
	cooldown -= 1;
}
