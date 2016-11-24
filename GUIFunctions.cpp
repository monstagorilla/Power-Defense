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

Tower *GUIFunctions::currentTower = nullptr;
GridPoint GUIFunctions::currentPos = GridPoint();
TowerType GUIFunctions::currentTowerType = basicTower;


void GUIFunctions::upgradeTower() {
    if (GUIFunctions::currentTower == nullptr) {
        return;
    }
    if (currentTower->currentUpgrade < currentTower->getMaxUpgrade()) {
        currentTower->currentUpgrade++;
        gamestats.money -= currentTower->getStats().price;
        currentTower->sprites.clear();
        for (auto path: currentTower->getStats().paths) {
            currentTower->sprites.push_back(Sprite(currentTower->pos, TILE_WIDTH, TILE_HEIGHT, path));
        }
    }
}

void GUIFunctions::setLabelPoint() {
    // root->getChild(GUI::paths[path_globalstats_point])->text = std::to_string(gamestats.points);
}

void GUIFunctions::setLabelMoney() {
    //root->getChild(GUI::paths[path_globalstats_money])->text = std::to_string(gamestats.money);
}

void GUIFunctions::inactivateMenus() {
    for (auto element: root->getChild(GUI::paths[path_menus_buy])->traverse()) {
        element->isActivated = false;
    }
    for (auto element: root->getChild(GUI::paths[path_menus_tower])->traverse()) {
        element->isActivated = false;
    }
}

void GUIFunctions::onClickTower() {
    inactivateMenus();
    currentPos = mousePos.snap();
    for (auto element: root->getChild(GUI::paths[path_menus_tower])->children) {
        element->isActivated = true;
    }

    for (int i = 0; i < allGameObjects.size(); i++) {
        if (allGameObjects[i]->ID == 2 && allGameObjects[i]->pos.snap() == currentPos) {
            currentTower = (Tower *) allGameObjects[i].get();
            return;
        }
    }

}

void GUIFunctions::onClickGround() {
    inactivateMenus();
    if (map.isGround(mousePos.snap())) {
        return;
    }
    for (auto element: root->getChild(GUI::paths[path_menus_buy])->traverse()) {
        element->isActivated = true;
    }
    root->getChild(GUI::paths[path_menus_buy_apply])->isActivated = false;
    currentPos = mousePos.snap();
    currentTowerType = basicTower;
    currentTower = nullptr;
    /*
    root->getChild(GUI::paths[path_menus_buy_container_type])->text = "";
    root->getChild(GUI::paths[path_menus_buy_container_damage])->text = "";
    root->getChild(GUI::paths[path_menus_buy_container_reloadTime])->text = "";
    root->getChild(GUI::paths[path_menus_buy_container_range])->text = "";
    root->getChild(GUI::paths[path_menus_buy_container_cost])->text = "";
     */
    for (auto object: root->getChild(GUI::paths[path_menus_buy_container])->children) {
        object->isActivated = false;
    }
    root->getChild(GUI::paths[path_temp_towerpreview])->isActivated = false;

}

void GUIFunctions::sellTower() {
    //add Implementation
}

void GUIFunctions::startGame() {
    gameIsRunning = true;
}

void GUIFunctions::endGame() {
    gameIsRunning = false;
}

void GUIFunctions::pause() {
    if (gameIsRunning) {
        gameIsRunning = false;
        root->getChild(GUI::paths[path_menus_main_pause])->text = "Continue";
    } else {
        gameIsRunning = true;
        root->getChild(GUI::paths[path_menus_main_pause])->text = "Pause";
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

void GUIFunctions::onClickTowerSymbol() {
    for (auto object: root->getChild(GUI::paths[path_menus_buy_container])->children) {
        object->isActivated = true;
    }
    std::string type = "";
    int damage = 0;
    int reloadTime = 0;
    int range = 0;
    int cost = 0;
    Symbol *towerPreview = (Symbol *) root->getChild(GUI::paths[path_temp_towerpreview]);
    towerPreview->sprites.clear();
    std::vector<std::string> towerSprites;

    switch (currentTowerType) {
        case basicTower:
            type = "BASIC TOWER";
            damage = BasicTower::stat[0].damage;
            reloadTime = BasicTower::stat[0].reloadTime;
            range = (int) BasicTower::stat[0].range;
            cost = BasicTower::stat[0].price;
            for(auto element: BasicTower::stat[0].paths){
                towerPreview->sprites.push_back(Sprite(currentPos.center(), TILE_WIDTH, TILE_HEIGHT, element));
            }
            break;
        case nailGun:
            type = "NAIL GUN";
            damage = NailGun::stat[0].damage;
            reloadTime = NailGun::stat[0].reloadTime;
            range = (int) NailGun::stat[0].range;
            cost = NailGun::stat[0].price;
            for(auto element: NailGun::stat[0].paths){
                towerPreview->sprites.push_back(Sprite(currentPos.center(), TILE_WIDTH, TILE_HEIGHT, element));
            }
            break;
    }
    root->getChild(GUI::paths[path_menus_buy_container_type])->text = type;
    root->getChild(GUI::paths[path_menus_buy_container_damage])->text = std::to_string(damage);
    root->getChild(GUI::paths[path_menus_buy_container_reloadTime])->text = std::to_string(reloadTime);
    root->getChild(GUI::paths[path_menus_buy_container_range])->text = std::to_string(range);
    root->getChild(GUI::paths[path_menus_buy_container_cost])->text = std::to_string(cost);
    root->getChild(GUI::paths[path_menus_buy_apply])->isActivated = true;
    root->getChild(GUI::paths[path_temp_towerpreview])->isActivated = true;

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
        }
        gamestats.money -= price;
        for (auto element: root->getChild(GUI::paths[path_mapOverlays])->children) {
            if (element->pos.snap() == currentPos) {
                element->onClick = onClickTower;
            }
        }
        root->getChild(GUI::paths[path_temp_towerpreview])->isActivated = false;
    }
}

void GUIFunctions::onClickBuyMenu_Cancel() {
    currentTowerType = basicTower;
    inactivateMenus();
    root->getChild(GUI::paths[path_temp_towerpreview])->isActivated = false;
}