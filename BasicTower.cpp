#include <memory>
#include <SDL2/SDL_mixer.h>
#include "Point.h"
#include "GameObject.h"
#include "BasicShot.h"
#include "BasicTower.h"
#include "Enemy.h"
#include "globals.h"
#include "util.h"
#include "config.h"
#include "Cache.h"

const std::vector<TowerStats> BasicTower::stat =
        //reloadTime, range, price, damage path
        {{20, 100, 100, 10, {"/assets/TowerBase.png", "/assets/TowerTurret.png"}},
         {20, 120, 50,  20, {"/assets/TowerBase.png", "/assets/TowerTurret1.png"}},
         {20, 150, 75,  30, {"/assets/TowerBase.png", "/assets/TowerTurret2.png"}},
         {10, 200, 100, 40, {"/assets/TowerBase.png", "/assets/TowerTurret3.png"}}};

BasicTower::BasicTower(const GridPoint pos) : Tower::Tower(pos, this->stat[0].paths) {

}

BasicTower::~BasicTower() {

}

void BasicTower::shoot(Enemy *target, const float angle) {
    allGameObjects.push_back(std::make_unique<BasicShot>(pos, this, target, getStats().damage, angle - 90.0f, 6.0, "/assets/Shot.png"));
    Mix_PlayChannel(-1, Cache::getSound("/audio/bao.wav"),0);
}

void BasicTower::update() {
    Enemy *nearest = nullptr;
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
            shoot(nearest, rotation);
            cooldown = getStats().reloadTime;
        }
    }
    cooldown--;
}

TowerStats BasicTower::getStats() {
    return stat[currentUpgrade];
}


TowerStats BasicTower::getStatsPrev() {
    if(currentUpgrade + 1 < stat.size()) {
        return stat[currentUpgrade + 1];
    }else{
        return TowerStats{};
    }
}

int BasicTower::getMaxUpgrade() {
    return (int) stat.size() - 1;
}

