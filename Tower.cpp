#include <vector>

#include "Point.h"
#include "Tower.h"
#include "Sprite.h"
#include "Enemy.h"

const std::vector<Stats> Tower::stat = {};

Tower::Tower(): GameObject::GameObject() {
    rotation = 0;
    currentUpgrade = 0;
    ID = 2 ;
    cooldown = 0;
    sprites = std::vector<Sprite>();
}

Tower::Tower(const GridPoint pos) : GameObject::GameObject(pos.center()){
    rotation = 0;
    currentUpgrade = 0;
    ID = 2;
    cooldown = 0;
    sprites = std::vector<Sprite>();
}

Tower::~Tower() {

}

Stats Tower::getStats() {

}

int Tower::getMaxUpgrade() {

}

void Tower::update() {

}

void Tower::shoot(Enemy *target) {

}
