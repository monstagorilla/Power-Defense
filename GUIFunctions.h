#pragma once

#include <memory>
#include "globals.h"
#include "Tower.h"
#include "Sprite.h"
#include "Point.h"
#include "gamestats.h"
#include "GUI.h"
#include "BasicTower.h"

Tower *currentTower = nullptr;
GridPoint currentPos = {0, 0};
//WTF??
extern std::string path_towermenu;
extern std::string path_buymenu;
extern std::string path_mapOverlays;
extern std::string path_menus;


void Tower(){
    /* set onClick of tile to onClickGround
    for(auto element: root->getChild(path_mapOverlays)->children){
        if(element->pos.snap() == currentPos){
            element->onClick = onClickTower();
        }
    }
     */
}

void upgradeTower() {
    if(currentTower == nullptr){
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

void setLabelPoint(){
    root->getChild("100")->text = std::to_string(gamestats.points);
}

void setLabelMoney(){
    root->getChild("102")->text = std::to_string(gamestats.money);
}

void inactivateMenus(){
    for(auto element: root->getChild(path_menus)->traverse()){
        element->isActivated = false;
    }
}

void onClickTower(){
    inactivateMenus();
    for(auto element: root->getChild(path_towermenu)->children){
        element->isActivated = true;
    }

    for (int i = 0; i < allGameObjects.size(); i++){
        if (allGameObjects[i]->ID == 2 && allGameObjects[i]->pos.snap() == currentPos){
            currentTower= (BasicTower *)allGameObjects[i].get(); // NASTY HACK !!!!!!!! ATTENTION: TODO: FIX this fucking OOP problem
            return;
        }
    }
}

void onClickGround (){
    inactivateMenus();
    for(auto element: root->getChild(path_buymenu)->children){
        element->isActivated = true;
    }
    currentPos = mousePos.snap();
    currentTower = nullptr;
}
void addBasicTower() {
    for (int i = 0; i < allGameObjects.size(); i++){
        if (allGameObjects[i].get()->ID == 2 && allGameObjects[i].get()->pos.snap() == currentPos){
            return;
        }
    }

    if (gamestats.money >= BasicTower::stat[0].price && currentPos.x >= 0 && currentPos.x < MAP_WIDTH && currentPos.y >= 0 && currentPos.y < MAP_HEIGHT && !map.isGround(currentPos)) {
        allGameObjects.push_back(std::make_unique<BasicTower>(currentPos));
        gamestats.money -= BasicTower::stat[0].price ;
        for(auto element: root->getChild(path_mapOverlays)->children){
            if(element->pos.snap() == currentPos){
                element->onClick = onClickTower;
            }
        }
    }
}

void sellTower(){
    //add Implementation
}
void startGame(){
    gameIsRunning = true;
}

void endGame(){
    gameIsRunning= false;
}