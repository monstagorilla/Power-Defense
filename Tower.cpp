#include <vector>

#include "Point.h"
#include "Tower.h"
#include "Enemy.h"
#include "config.h"
#include "Sprite.h"

const std::vector<TowerStats> Tower::stat = {};

Tower::Tower(): GameObject::GameObject() {
    rotation = 0;
    currentUpgrade = 0;
    ID = 2 ;
    cooldown = 0;
    sprites = std::vector<Sprite>();
    for (auto path: stat[0].paths) {
        sprites.push_back(Sprite(pos, TILE_WIDTH, TILE_HEIGHT, path, true));
    }
}

Tower::Tower(const GridPoint pos, const std::vector<std::string> paths) : GameObject::GameObject(pos.center()){
    rotation = 0;
    currentUpgrade = 0;
    ID = 2;
    cooldown = 0;
    sprites = std::vector<Sprite>();
    for (auto path: paths) {
        sprites.push_back(Sprite(pos.center(), TILE_WIDTH, TILE_HEIGHT, path, true));
    }
}

Tower::~Tower() {

}

TowerStats Tower::getStats() {

}

int Tower::getMaxUpgrade() {

}

void Tower::update() {

}

void Tower::shoot(Enemy *target) {

}
