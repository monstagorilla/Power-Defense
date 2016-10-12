#pragma once

#include <memory>
#include "globals.h"
#include "BasicTower.h"
#include "Sprite.h"
#include "Point.h"

static Tower *currentTower = nullptr;
static GridPoint currentPos = {0, 0};

void addBasicTower() {
    if (currentPos.x >= 0 && currentPos.x < MAP_WIDTH && currentPos.y >= 0 && currentPos.y < MAP_HEIGHT && !map.isGround(currentPos)) {
        allGameObjects.push_back(std::make_unique<BasicTower>(currentPos));
    }
}

void upgradeTower() {
    if (currentTower->currentUpgrade < currentTower->getMaxUpgrade()) {
        currentTower->currentUpgrade++;
        currentTower->sprites.clear();
        for (auto path: currentTower->stat[currentTower->currentUpgrade].paths) {
            currentTower->sprites.push_back(Sprite(currentTower->pos, TILE_WIDTH, TILE_HEIGHT, path));
        }
        std::cout << "scuuuurrrr" << std::endl;
    }
}
