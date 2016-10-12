#pragma once

#include <memory>
#include "globals.h"
#include "BasicTower.h"
#include "Sprite.h"
#include "Point.h"

static Tower *currentTower = nullptr;

void addBasicTower(const GridPoint pos) {
    if (pos.x >= 0 && pos.x < MAP_WIDTH && pos.y >= 0 && pos.y < MAP_HEIGHT && !map.isGround(pos)) {
        allGameObjects.push_back(std::make_unique<BasicTower>(pos));
    }
}

void upgradeTower() {
    currentTower->update();
    currentTower->sprites.clear();
    for (auto path: currentTower->stat[currentTower->currentUpgrade].paths) {
        currentTower->sprites.push_back(Sprite(currentTower->pos, TILE_WIDTH, TILE_HEIGHT, path));
    }
    std::cout << "scuuuurrrr" << std::endl;
}
