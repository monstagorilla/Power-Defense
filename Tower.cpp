#include "GameObject.h"
#include "Tower.h"
#include "Shot.h"
#include "util.h"
#include "globals.h"

#include <math.h>

extern SDL_Renderer *renderer;

const std::vector<stats> Tower::stat={};

Tower::Tower(const GridPoint pos) {
	this->pos = pos.center();
	rotation = 0;
	currentUpgrade = 0;
	ID = 2;
    cooldown = 0;
}

Tower::~Tower() {

}

stats Tower::getStats(){

}

int Tower::getMaxUpgrade(){

}
