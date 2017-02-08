#include <memory.h>

#include "GUIFunctions.h"
#include "Tower.h"
#include "globals.h"
#include "gamestats.h"
#include "GUI.h"
#include "GUIObject.h"
#include "BasicTower.h"
#include "Map.h"
#include "config.h"

#include "NailGun.h"
#include "GameObject.h"
#include "Symbol.h"
#include "Cache.h"
#include "SplashTower.h"
#include "WaveManager.h"

Tower *GUIFunctions::currentTower = nullptr;
GridPoint GUIFunctions::currentPos = GridPoint();
TowerType GUIFunctions::currentTowerType = basicTower;
bool GUIFunctions::hasStarted = false;

void GUIFunctions::upgradeTower() {
    if (GUIFunctions::currentTower == nullptr) {
        return;
    }
    if (currentTower->currentUpgrade < currentTower->getMaxUpgrade()) {
        currentTower->currentUpgrade++;
        gamestats.money -= currentTower->getStats().price;
        currentTower->sprites.clear();
        for (auto path: currentTower->getStats().paths) {
            currentTower->sprites.push_back(Sprite(currentTower->pos, TILE_WIDTH, TILE_HEIGHT, path, true));
        }
        Mix_PlayChannel(-1, Cache::getSound("/audio/upgrade.wav"),0);
    }
    updateContainerTowerstats();
}

void GUIFunctions::setLabelPoint() {
    root->getChild(lblPoint)->text = std::to_string(gamestats.points);
}

void GUIFunctions::setLabelMoney() {
    root->getChild(lblMoney)->text = std::to_string(gamestats.money);
}

void GUIFunctions::setLabelWaveCount() {
    root->getChild(lblWaveCount)->text = std::to_string(gamestats.nextWave);
}

void GUIFunctions::setLabelLevel() {
    root->getChild(lblLevel)->text = std::to_string(gamestats.level);
}

void GUIFunctions::setLabelLives() {
    root->getChild(lblLives)->text = std::to_string(gamestats.lives);
}

void GUIFunctions::inactivateMenus() {
    for (auto element: root->getChild(menus_buy)->traverse()) {
        element->isActivated = false;
    }
    for (auto element: root->getChild(menus_tower)->traverse()) {
        element->isActivated = false;
    }
}

void GUIFunctions::onClickTower() {
    inactivateMenus();
    currentPos = mousePos.snap();
    for (auto element: root->getChild(menus_tower)->children) {
        element->isActivated = true;
    }

    for (auto element : root->getChild(menus_buy_container)->children) {
        element->isActivated = true;
    }
    root->getChild(menus_buy_container)->isActivated = true;

    for (int i = 0; i < allGameObjects.size(); i++) {
        if (allGameObjects[i]->ID == 2 && allGameObjects[i]->pos.snap() == currentPos) {
            currentTower = (Tower *) allGameObjects[i].get();
            break;
        }
    }
    updateContainerTowerstats();
}

void GUIFunctions::updateContainerTowerstats() {
    std::string type;
    switch (currentTowerType) {
        case basicTower:
            type = "BASIC TOWER";
            break;
        case nailGun:
            type = "NAIL GUN";
            break;
        case splashTower:
            type = "SPLASH TOWER";
            break;
    }
    root->getChild(lblBuyTitleMain)->text = type;
    if (currentTower != nullptr) {
        root->getChild(lblBuyDamage)->text =
                std::to_string(currentTower->getStats().damage) + "  (->" +
                std::to_string(currentTower->getStatsPrev().damage) + ")";
        root->getChild(lblBuyReloadTime)->text =
                std::to_string(currentTower->getStats().reloadTime) + "  (->" +
                std::to_string(currentTower->getStatsPrev().reloadTime) + ")";
        root->getChild(lblBuyRange)->text =
                std::to_string((int) currentTower->getStats().range) + "  (->" +
                std::to_string((int) currentTower->getStatsPrev().range) + ")";
        root->getChild(lblBuyCost)->text = std::to_string(
                currentTower->getStats().price);
    }
}

void GUIFunctions::onClickGround() {
    if (map.isGround(mousePos.snap()) || currentPos == mousePos.snap()) {
        return;
    }
    inactivateMenus();
    for (auto element: root->getChild(menus_buy)->children) {
        element->isActivated = true;
    }
    root->getChild(buttonBuyOK)->isActivated = false;
    currentPos = mousePos.snap();
    currentTower = nullptr;
    for (auto object: root->getChild(menus_buy_container)->children) {
        object->isActivated = false;
    }
    root->getChild(symbolTemp)->isActivated = false;
}

void GUIFunctions::sellTower() {
    //add Implementation
}

void GUIFunctions::startGame() {
    gameIsRunning = true;
}

void GUIFunctions::endGame() {
    gameIsRunning = false;
    Mix_PlayChannel(-1, Cache::getSound("/audio/nein.wav"),0);
    Mix_PauseMusic();
}

void GUIFunctions::pause() {
    if (!hasStarted) {
        hasStarted = true;
    }
    if (gameIsRunning) {
        gameIsRunning = false;
        root->getChild(buttonStart)->text = "Continue";
        root->getChild(buttonNewWave)->isActivated = false;
    } else {
        gameIsRunning = true;
        root->getChild(buttonStart)->text = "Pause";
        root->getChild(buttonNewWave)->isActivated = true;
    }
}


void GUIFunctions::onClickSymbol_BasicTower() {
    currentTowerType = basicTower;
    onClickTowerSymbol();
}


void GUIFunctions::onClickSymbol_NailGun() {
    currentTowerType = nailGun;
    onClickTowerSymbol();
}

void GUIFunctions::onClickSymbol_SplashTower() {
    currentTowerType = splashTower;
    onClickTowerSymbol();
}

void GUIFunctions::onClickTowerSymbol() {
    for (auto object: root->getChild(menus_buy_container)->children) {
        object->isActivated = true;
    }
    std::string type = "";
    int damage = 0;
    int reloadTime = 0;
    int range = 0;
    int cost = 0;
    int damagePrev = 0;
    int reloadTimePrev = 0;
    int rangePrev = 0;
    Symbol *towerPreview = (Symbol *) root->getChild(symbolTemp);
    towerPreview->sprites.clear();
    std::vector<std::string> towerSprites;

    switch (currentTowerType) {
        case basicTower:
            type = "BASIC TOWER";
            if (BasicTower::stat.size() >= 2) {
                damage = BasicTower::stat[0].damage;
                damagePrev = BasicTower::stat[1].damage;
                reloadTime = BasicTower::stat[0].reloadTime;
                reloadTimePrev = BasicTower::stat[1].reloadTime;
                range = (int) BasicTower::stat[0].range;
                rangePrev = (int) BasicTower::stat[1].range;
                cost = BasicTower::stat[0].price;
            } else {
                std::cout << "too small stat vector to display stats!" << std::endl;
            }
            for (auto element: BasicTower::stat[0].paths) {
                towerPreview->sprites.push_back(Sprite(currentPos.center(), TILE_WIDTH, TILE_HEIGHT, element, true));
            }
            break;
        case nailGun:
            type = "NAIL GUN";
            if (NailGun::stat.size() >= 2) {
                damage = NailGun::stat[0].damage;
                damagePrev = NailGun::stat[1].damage;
                reloadTime = NailGun::stat[0].reloadTime;
                reloadTimePrev = NailGun::stat[1].reloadTime;
                range = (int) NailGun::stat[0].range;
                rangePrev = (int) NailGun::stat[1].range;
                cost = NailGun::stat[0].price;
            } else {
                std::cout << "too small stat vector to display stats!" << std::endl;
            }
            for (auto element: NailGun::stat[0].paths) {
                towerPreview->sprites.push_back(Sprite(currentPos.center(), TILE_WIDTH, TILE_HEIGHT, element, true));
            }
            break;
        case splashTower:
            type = "SPLASH TOWER";
            if (SplashTower::stat.size() >= 2) {
                damage = SplashTower::stat[0].damage;
                damagePrev = SplashTower::stat[1].damage;
                reloadTime = SplashTower::stat[0].reloadTime;
                reloadTimePrev = SplashTower::stat[1].reloadTime;
                range = (int) SplashTower::stat[0].range;
                rangePrev = (int) SplashTower::stat[1].range;
                cost = SplashTower::stat[0].price;
            } else {
                std::cout << "too small stat vector to display stats!" << std::endl;
            }
            for (auto element: SplashTower::stat[0].paths) {
                towerPreview->sprites.push_back(Sprite(currentPos.center(), TILE_WIDTH, TILE_HEIGHT, element, true));
            }
            break;
    }
    towerPreview->pos.x = currentPos.center().x;
    towerPreview->pos.y = currentPos.center().y;

    root->getChild(lblBuyTitleMain)->text = type;
    root->getChild(lblBuyDamage)->text =
            std::to_string(damage) + "  (->" + std::to_string(damagePrev) + ")";
    root->getChild(lblBuyReloadTime)->text =
            std::to_string(reloadTime) + "  (->" + std::to_string(reloadTimePrev) + ")";
    root->getChild(lblBuyRange)->text =
            std::to_string(range) + "  (->" + std::to_string(rangePrev) + ")";
    root->getChild(lblBuyCost)->text = std::to_string(cost);
    root->getChild(buttonBuyOK)->isActivated = true;
    root->getChild(symbolTemp)->isActivated = true;
}

void GUIFunctions::onClickBuyMenu_Apply() {
    for (int i = 0; i < allGameObjects.size(); i++) {
        if (allGameObjects[i].get()->ID == 2 && allGameObjects[i].get()->pos.snap() == currentPos) {
            return;
        }
    }
    int price = 0;
    switch (currentTowerType) {
        case basicTower:
            price = BasicTower::stat[0].price;
            break;
        case nailGun:
            price = NailGun::stat[0].price;
            break;
        case splashTower:
            price = SplashTower::stat[0].price;
            break;
        default:
            return;
    }
    if (gamestats.money >= price && currentPos.x >= 0 && currentPos.x < MAP_WIDTH &&
        currentPos.y >= 0 && currentPos.y < MAP_HEIGHT && !map.isGround(currentPos)) {
        switch (currentTowerType) {
            case basicTower:
                allGameObjects.push_back(std::make_unique<BasicTower>(currentPos));
                break;
            case nailGun:
                allGameObjects.push_back(std::make_unique<NailGun>(currentPos));
                break;
            case splashTower:
                allGameObjects.push_back(std::make_unique<SplashTower>(currentPos));
                break;
        }
        gamestats.money -= price;
        root->getChild(symbolTemp)->isActivated = false;
        for (int i = 0; i < allGameObjects.size(); i++) {
            if (allGameObjects[i]->ID == 2 && allGameObjects[i]->pos.snap() == currentPos) {
                currentTower = (Tower *) allGameObjects[i].get();
                break;
            }
        }
        for (auto element: root->getChild(mapOverlays)->children) {
            if (element->pos.snap() == currentPos) {
                element->onClick = onClickTower;
                inactivateMenus();
                break;
            }
        }
        for (auto object: root->getChild(menus_tower)->children) {
            object->isActivated = true;
        }
        for (auto element: root->getChild(menus_buy_container)->children) {
            element->isActivated = true;
        }
        root->getChild(menus_buy_container)->isActivated = true;
        Mix_PlayChannel(-1, Cache::getSound("/audio/upgrade.wav"),0);
    }
}

void GUIFunctions::onClickBuyMenu_Cancel() {
    currentTowerType = basicTower;
    inactivateMenus();
    root->getChild(symbolTemp)->isActivated = false;
}

void GUIFunctions::newWave() {
    waveManager.addWave();
}

void GUIFunctions::onClickMusicMute() {
    if (Cache::isMusicMuted) {
        root->getChild(buttonMusic)->text = "Music Off";
        Mix_VolumeMusic(64);
    }else{
        root->getChild(buttonMusic)->text = "Music On";
        Mix_VolumeMusic(0);
    }
    Cache::isMusicMuted = !Cache::isMusicMuted;
}

void GUIFunctions::onCLickSoundsMute() {
    if (Cache::isSoundMuted) {
        root->getChild(buttonFX)->text = "Fx Off";
    }else{
        root->getChild(buttonFX)->text = "Fx On";
    }
    Cache::isSoundMuted = !Cache::isSoundMuted;
}