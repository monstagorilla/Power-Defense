#pragma once

class Tower;

#include <memory>

#include "Point.h"

class GUIFunctions{
public:
    static Tower* currentTower;
    static GridPoint currentPos;

    static void upgradeTower();
    static void setLabelPoint();
    static void setLabelMoney();
    static void inactivateMenus();
    static void onClickTower();
    static void sellTower();
    static void addBasicTower();
    static void addNailGun();
    static void startGame();
    static void onClickGround();
    static void endGame();
};