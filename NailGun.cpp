#include <algorithm>
#include <SDL2/SDL_mixer.h>
#include "NailGun.h"
#include "globals.h"
#include "BasicShot.h"
#include "util.h"
#include "Point.h"
#include "Enemy.h"
#include "Cache.h"

const std::vector<TowerStats> NailGun::stat =
        //reloadTime, range, price, damage, path
        {{10, 120, 100, 1, {"/assets/TowerBase.png", "/assets/NailgunTurret.png"}},
         {10, 120, 50,  2, {"/assets/TowerBase.png", "/assets/NailgunTurret.png"}},
         {5,  150, 75,  3, {"/assets/TowerBase.png", "/assets/NailgunTurret.png"}},
         {5,  200, 100, 4, {"/assets/TowerBase.png", "/assets/NailgunTurret.png"}}};

NailGun::NailGun(const GridPoint pos) : Tower(pos, stat[0].paths) {

}
    
NailGun::~NailGun() {

}

void NailGun::update() {
    struct candidateEnemy {
        Enemy* eptr;
        float  distance;
        bool operator <(candidateEnemy other) {
            return this->distance < other.distance;
        }
    };
    std::vector<candidateEnemy> candidates;
    for (int i = 0; i < allGameObjects.size(); i++) {
        float dist = distance(allGameObjects[i]->pos, this->pos);
        if (allGameObjects[i]->ID == 1 && dist < getStats().range) {
            candidates.push_back(candidateEnemy{ (Enemy *) allGameObjects[i].get(), dist });
        }
    }
    if (not candidates.empty()) {
        std::sort(candidates.begin(), candidates.end());
        const auto primary = candidates[0].eptr;
        rotation = atan2(primary->pos.y - this->pos.y, 
                   primary->pos.x - this->pos.x) * 180.0 / M_PI + 90;
        sprites[1].rotation = rotation;
        if (cooldown <= 0) {
            for(int i = 0; i < std::min((int)candidates.size(), 3); i++){
                /* parabolic magic to make the nails spread out like this:
                 *            |  30°           x
                 *  [1][0][2] |                /
                 *    \ | /   |   0° x        /
                 *            |       \      /
                 *     (O)    | -30°   \__x_/
                 *            |      [0] [1] [2]
                 */
                shoot(candidates[i].eptr, rotation + 30.0f * (2*i*i - 3*i));
            }
            cooldown = getStats().reloadTime;
        }
    }

    cooldown--;
}

void NailGun::shoot(Enemy *target, const float angle) {
    allGameObjects.push_back(std::make_unique<BasicShot>(pos, this, target, getStats().damage, angle - 90.0f, 10.0, "/assets/Nail.png"));
    Mix_PlayChannel(-1, Cache::getSound("/audio/brrt.wav"), 0);
}

TowerStats NailGun::getStats() {
    return stat[currentUpgrade];
}

TowerStats NailGun::getStatsPrev() {
    if(currentUpgrade + 1 < stat.size()) {
        return stat[currentUpgrade + 1];
    }else{
        return TowerStats{};
    }
}

int NailGun::getMaxUpgrade() {
    return (int) stat.size() - 1;
}



