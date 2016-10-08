#include "GameObject.h"
#include "Tower.h"
#include "Shot.h"
#include "util.h"
#include "globals.h"

#include <math.h>

extern SDL_Renderer *renderer;

Tower::Tower(const GridPoint pos) {
	this->pos = pos.center();
	rotation = 0;
	currentUpgrade = 0;
	ID = 2;
}

Tower::~Tower() {

}

stats Tower::getStats(){	
	return stat[currentUpgrade];
}

int Tower::getMaxUpgrade(){
	return stat.size() - 1;
}
