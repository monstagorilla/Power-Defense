#pragma once

class Tower;

#include <memory>

#include "Point.h"

enum TowerType{
    basicTower = 0,
    nailGun = 1
};

class GUIFunctions{
public:
    static Tower* currentTower;
    static GridPoint currentPos;
    static TowerType currentTowerType;

    static void upgradeTower();
    static void setLabelPoint();
    static void setLabelMoney();
    static void inactivateMenus();
    static void onClickTower();
    static void sellTower();
    static void startGame();
    static void onClickGround();
    static void endGame();
    static void pause();
    static void onClickSymbol_BasicTower();
    static void onClickSymbol_NailGun();
    static void onClickBuyMenu_Apply();
    static void onClickBuyMenu_Cancel();
};