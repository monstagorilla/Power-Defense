#pragma once

#include <memory>
#include "globals.h"
#include "BasicTower.h"
#include "Sprite.h"
#include "Point.h"
#include "gamestats.h"
#include "GUI.h"

static Tower *currentTower = nullptr;
static GridPoint currentPos = {0, 0};

void addBasicTower() {
    if (gamestats.money >= BasicTower::getStats().price&& currentPos.x >= 0 && currentPos.x < MAP_WIDTH && currentPos.y >= 0 && currentPos.y < MAP_HEIGHT && !map.isGround(currentPos)) {
        allGameObjects.push_back(std::make_unique<BasicTower>(currentPos));
        gamestats.money -= BasicTower::getStats().price
    }
}

void upgradeTower() {
    if (currentTower->currentUpgrade < currentTower->getMaxUpgrade()) {
        currentTower->currentUpgrade++;
        currentTower->sprites.clear();
        for (auto path: currentTower->stat[currentTower->currentUpgrade].paths) {
            currentTower->sprites.push_back(Sprite(currentTower->pos, TILE_WIDTH, TILE_HEIGHT, path));
        }
    }
}

static void setLabelPoint(){
    root->getChild("100")->text = std::to_string(gamestats.points);
}

void setLabelMoney(){
    root->getChild("102")->text = std::to_string(gamestats.money);
}