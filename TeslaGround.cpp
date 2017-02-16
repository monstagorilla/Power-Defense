#include "TeslaGround.h"

//reloadTime, range, price, damage path
const std::vector<TowerStats> TeslaGround::stat =
        {{20, 0, 100, 10, {"/assets/TowerBase.png", "/assets/TowerTurret.png"}}};


TeslaGround::TeslaGround(const GridPoint pos): Tower(pos, stat[0].paths) {
    ID = 5;
}

TeslaGround::~TeslaGround() {

}



TowerStats TeslaGround::getStats() {
    return stat[currentUpgrade];
}


TowerStats TeslaGround::getStatsPrev() {
    return getStats(); //no upgrades available
}

int TeslaGround::getMaxUpgrade() {
    return (int) stat.size() - 1;
}

void TeslaGround::update() {

}

void TeslaGround::shoot() {

}
