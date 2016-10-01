#pragma once

#include "stats.h"
#include "colors.h"

static void drawStats (){
	TextOutput::getInstance()->drawText("ENEMYCOUNT: " + std::to_string(getEnemyCount()), MAP_WIDTH * TILE_WIDTH + 20, 20,200, 40, 0, COLOR_BLUE);
}