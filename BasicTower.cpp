#include <memory>

#include "Point.h"
#include "GameObject.h"
#include "Shot.h"
#include "BasicTower.h"
#include "Enemy.h"
#include "globals.h"
#include "util.h"
#include "config.h"

const std::vector<Stats> BasicTower::stat =
        {{20, 100, 100, 10, {"/assets/TowerBase.png", "/assets/TowerTurret.png"}},
         {20, 100, 50,  20, {"/assets/TowerBase.png", "/assets/TowerTurret1.png"}},
         {20, 100, 75,  30, {"/assets/TowerBase.png", "/assets/TowerTurret2.png"}},
         {15, 125, 100, 40, {"/assets/TowerBase.png", "/assets/TowerTurret3.png"}}};

BasicTower::BasicTower(const GridPoint pos) : Tower::Tower(pos) {
    for (auto path: stat[0].paths) {
        sprites.push_back(Sprite(pos.center(), TILE_WIDTH, TILE_HEIGHT, path));
    }
}

BasicTower::~BasicTower() {

}

void BasicTower::shoot(Enemy *target) {
    allGameObjects.push_back(std::make_unique<Shot>(pos, this, target, getStats().damage));
}

void BasicTower::update() {
    Enemy *nearest = NULL;
    auto shortestDist = getStats().range;
    for (int i = 0; i < allGameObjects.size(); i++) {
        if (allGameObjects[i]->ID == 1 &&
            distance(allGameObjects[i]->pos, this->pos) <
            shortestDist) {
            nearest = (Enemy *) allGameObjects[i].get();
            shortestDist = distance(allGameObjects[i]->pos, this->pos);
        }
    }
    if (nearest != NULL && shortestDist <= getStats().range) {
        rotation = atan2(nearest->pos.y - this->pos.y,
                         nearest->pos.x - this->pos.x) * 180.0 /
                   M_PI + 90;
        sprites[1].rotation = rotation;
        if (cooldown <= 0) {
            shoot(nearest);
            cooldown = getStats().reloadTime;
        }
    }
    cooldown--;
}

Stats BasicTower::getStats() {
    return stat[currentUpgrade];
}

int BasicTower::getMaxUpgrade() {
    return (int) stat.size() - 1;
}