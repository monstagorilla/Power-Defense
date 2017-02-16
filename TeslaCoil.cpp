#include "TeslaCoil.h"
#include "TeslaGround.h"
#include "globals.h"
#include "util.h"
#include "Cache.h"
#include "Lightning.h"

const std::vector<TowerStats> TeslaCoil::stat =
        //reloadTime, range, price, damage path
        {{100, 100, 100, 10, {"/assets/TowerBase.png", "/assets/TowerTurret.png"}},
         {20, 120, 50,  20, {"/assets/TowerBase.png", "/assets/TowerTurret1.png"}},
         {20, 150, 75,  30, {"/assets/TowerBase.png", "/assets/TowerTurret2.png"}},
         {10, 200, 100, 40, {"/assets/TowerBase.png", "/assets/TowerTurret3.png"}}};

TeslaCoil::TeslaCoil(const GridPoint pos) : Tower::Tower(pos, this->stat[0].paths) {

}

TeslaCoil::~TeslaCoil() {

}

void TeslaCoil::shoot(TeslaGround* target) {
    allGameObjects.push_back(std::make_unique<Lightning>(pos, target->pos, 0.2));
    Mix_PlayChannel(-1, Cache::getSound("/audio/bao.wav"),0);
}

void TeslaCoil::update() {
    std::vector<TeslaGround *> grounds;
    auto range = getStats().range;
    for (int i = 0; i < allGameObjects.size(); i++) {
        if (allGameObjects[i]->ID == 5 &&
            distance(allGameObjects[i]->pos, this->pos) < range) {
            grounds.push_back((TeslaGround *) allGameObjects[i].get());
        }
    }
    if (cooldown <= 0) {
        for (auto element: grounds) {
            shoot(element);
        }
        cooldown = getStats().reloadTime;
    }
    cooldown--;
}

TowerStats TeslaCoil::getStats() {
    return stat[currentUpgrade];
}


TowerStats TeslaCoil::getStatsPrev() {
    if(currentUpgrade + 1 < stat.size()) {
        return stat[currentUpgrade + 1];
    }else{
        return TowerStats{};
    }
}

int TeslaCoil::getMaxUpgrade() {
    return (int) stat.size() - 1;
}

