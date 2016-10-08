#pragma once

#include "globals.h"

static int getEnemyCount() {
	int counter = 0;
	for (auto& object : allGameObjects) {
		if (object->ID == 1){
			counter++;
		}
	}
	return counter;
}
