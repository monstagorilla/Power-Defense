#include "GUIFunctions.h"
#include "Tower.h"
#include "globals.h"
#include "gamestats.h"
#include "GUI.h"
#include "GUIObject.h"
#include "BasicTower.h"
#include "Map.h"

Tower* GUIFunctions::currentTower = nullptr;
GridPoint GUIFunctions::currentPos = GridPoint();


void GUIFunctions::upgradeTower() {
    if(GUIFunctions::currentTower == nullptr){
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

void GUIFunctions::setLabelPoint(){
    root->getChild(GUI::paths[path_globalstats_point])->text = std::to_string(gamestats.points);
}

void GUIFunctions::setLabelMoney(){
    root->getChild(GUI::paths[path_globalstats_money])->text = std::to_string(gamestats.money);
}

void GUIFunctions::inactivateMenus(){
    for(auto element: root->getChild(GUI::paths[path_menus])->traverse()){
        element->isActivated = false;
    }
}

void GUIFunctions::onClickTower(){
    inactivateMenus();
    for(auto element: root->getChild(GUI::paths[path_towermenu])->children){
        element->isActivated = true;
    }

    for (int i = 0; i < allGameObjects.size(); i++){
        if (allGameObjects[i]->ID == 2 && allGameObjects[i]->pos.snap() == currentPos){
            currentTower = (Tower *) allGameObjects[i].get();
            return;
        }
    }
}

void GUIFunctions::onClickGround (){
    inactivateMenus();
    for(auto element: root->getChild(GUI::paths[path_buymenu])->children){
        element->isActivated = true;
    }
    currentPos = mousePos.snap();
    currentTower = nullptr;
}
void GUIFunctions::addBasicTower() {
    for (int i = 0; i < allGameObjects.size(); i++){
        if (allGameObjects[i].get()->ID == 2 && allGameObjects[i].get()->pos.snap() == currentPos){
            return;
        }
    }

    if (gamestats.money >= BasicTower::stat[0].price && currentPos.x >= 0 && currentPos.x < MAP_WIDTH && currentPos.y >= 0 && currentPos.y < MAP_HEIGHT && !map.isGround(currentPos)) {
        allGameObjects.push_back(std::make_unique<BasicTower>(currentPos));
        gamestats.money -= BasicTower::stat[0].price ;
        for(auto element: root->getChild(GUI::paths[path_mapOverlays])->children){
            if(element->pos.snap() == currentPos){
                element->onClick = onClickTower;
            }
        }
    }
}

void GUIFunctions::sellTower(){
    //add Implementation
}
void GUIFunctions::startGame(){
    gameIsRunning = true;
}

void GUIFunctions::endGame(){
    gameIsRunning= false;
}