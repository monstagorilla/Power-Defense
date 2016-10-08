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
	rotation = 0;
	currentUpgrade = 0;
	ID = 2;
}

Tower::~Tower() {

}

stats Tower::getStats(){	
	return stat[currentUpgrade];
}
