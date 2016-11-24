#include <algorithm>
#include "NailGun.h"
#include "globals.h"
#include "BasicShot.h"
#include "util.h"
#include "Point.h"
#include "Enemy.h"

const std::vector<TowerStats> NailGun::stat =
        //reloadTime, range, price, damage, path
        {{10, 120, 100, 1, {"/assets/TowerBase.png", "/assets/TowerTurret.png"}},
         {10, 120, 50,  2, {"/assets/TowerBase.png", "/assets/TowerTurret1.png"}},
         {5,  150, 75,  3, {"/assets/TowerBase.png", "/assets/TowerTurret2.png"}},
         {5,  200, 100, 4, {"/assets/TowerBase.png", "/assets/TowerTurret3.png"}}};

NailGun::NailGun(const GridPoint pos) : Tower(pos, stat[0].paths) {

}

NailGun::~NailGun() {

}

void NailGun::update() {
    std::vector<Enemy *> nearest;
    for (int i = 0; i < allGameObjects.size(); i++) {
        if (allGameObjects[i]->ID == 1 && distance(allGameObjects[i]->pos, this->pos) < getStats().range) {
            nearest.push_back((Enemy *) allGameObjects[i].get());
        }
    }

    /*
    int i;
    if (nearest.size() > 2) {
        i = 3;
    } else {
        i = (int) nearest.size();
    }

    while (i > 0) {
        if (nearest[nearest.size() - i] != nullptr) {
            rotation = atan2(nearest[nearest.size() - i]->pos.y - this->pos.y, nearest[nearest.size() - i]->pos.x -
                                                                       this->pos.x * 180.0 / M_PI + 90);
            sprites[1].rotation = rotation;
            if (cooldown <= 0) {
                shoot(nearest[nearest.size() - i], rotation + (i -2) * M_PI / 4.0 );
                cooldown = getStats().reloadTime;
            }
        }
        i--;
    }
     */

    //TODO: just three targets
    if (cooldown <= 0) {
        for (auto element: nearest) {
            rotation = atan2(element->pos.y - this->pos.y, element->pos.x - this->pos.x * 180.0 / M_PI + 90);
            sprites[1].rotation = rotation;

            shoot(element, rotation);
        }
        cooldown = getStats().reloadTime;
    }
    nearest.clear();
    cooldown--;
}

void NailGun::shoot(Enemy *target, const float angle) {
    allGameObjects.push_back(std::make_unique<BasicShot>(pos, this, target, getStats().damage, angle, 10.0));
}

TowerStats NailGun::getStats() {
    return stat[currentUpgrade];
}

int NailGun::getMaxUpgrade() {
    return (int) stat.size() - 1;
}



