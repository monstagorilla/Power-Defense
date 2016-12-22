#include "SplashTower.h"
#include "Point.h"
#include "globals.h"
#include "Enemy.h"
#include "util.h"
#include "Grenade.h"

const std::vector<TowerStats> SplashTower::stat =
        //reloadTime, range, price, damage path
        {{50, 100, 100, 20, {"/assets/TowerBase.png", "/assets/GrenadeTurret.png"}},
         {50, 120, 50,  30, {"/assets/TowerBase.png", "/assets/GrenadeTurret1.png"}},
         {50, 150, 75,  40, {"/assets/TowerBase.png", "/assets/GrenadeTurret2.png"}},
         {40, 200, 100, 60, {"/assets/TowerBase.png", "/assets/GrenadeTurret3.png"}}};

SplashTower::SplashTower(const GridPoint pos) : Tower::Tower(pos, stat[0].paths) {

}

SplashTower::~SplashTower() {

}

void SplashTower::update() {
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
    if (nearest != nullptr && shortestDist <= getStats().range) {
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

void SplashTower::shoot(Enemy *target, const float angle) {
    allGameObjects.push_back(std::make_unique<Grenade>(pos, this, target, getStats().damage, angle - 90.0f, 6.0));
}

TowerStats SplashTower::getStats() {
    return stat[currentUpgrade];
}

int SplashTower::getMaxUpgrade() {
    return (int) stat.size() - 1;
}
