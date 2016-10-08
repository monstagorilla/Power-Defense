#include <memory> 

#include "globals.h"
#include "BasicTower.h"
#include "Sprite.h"

void addBasicTower(const GridPoint pos){
	if(pos.x > 0 && pos.x < MAP_WIDTH && pos.y > 0 && pos.y < MAP_HEIGHT && map.isGround(pos)){
		allGameObjects.push_back(std::make_unique <BasicTower>(x, y));
	}
}

void upgradeTower(Tower& tower){
	tower.currentUpgrade++; 
	tower.sprites.clear();
	for(auto path: tower.stat[tower.currentUpgrade].paths){
		tower.sprites.push_back(Sprite(tower.pos.x, tower.pos.y, TILE_WIDTH, TILE_HEIGHT, path));
	}
}


