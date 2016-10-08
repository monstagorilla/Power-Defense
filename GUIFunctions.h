#include <memory> 

#include "globals.h"
#include "BasicTower.h"
#include "Sprite.h"
#include "Point.h"

void addBasicTower(const GridPoint pos){
	if(pos.x >= 0 && pos.x < MAP_WIDTH && pos.y >= 0 && pos.y < MAP_HEIGHT && !map.isGround(pos)){
		allGameObjects.push_back(std::make_unique <BasicTower>(pos));
	}
}

void upgradeTower(Tower& tower){
	tower.currentUpgrade++; 
	tower.sprites.clear();
	for(auto path: tower.stat[tower.currentUpgrade].paths){
		tower.sprites.push_back(Sprite(tower.pos, TILE_WIDTH, TILE_HEIGHT, path));
	}
}



