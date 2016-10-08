#include <memory> 

#include "globals.h"
#include "BasicTower.h"

void addBasicTower(const int x, const int y){
	if(x > 0 && x < MAP_WIDTH && y > 0 && < MAP_HEIGHT){
		allGameObjects.push_back(std::make_unique <BasicTower>(x, y));
	}
}

void upgradeTower(const Tower& tower){
	tower.currentUpgrade++; 
}


