#pragma once

class Tower;

#include <memory>

#include "Point.h"

enum TowerType{
    basicTower,
    nailGun,
    splashTower,
    teslaCoil,
    teslaGround
};

class GUIFunctions{
public:
    static Tower* currentTower;
    static GridPoint currentPos;
    static TowerType currentTowerType;

    static void upgradeTower();
    static void setLabelPoint();
    static void setLabelMoney();
    static void setLabelWaveCount();
    static void setLabelLevel();
    static void setLabelLives();
    static void onClickTower();
    static void sellTower();
    static void startGame();
    static void newWave();
    static void onClickGround();
    static void endGame();
    static void pause();
    static void onClickSymbol_BasicTower();
    static void onClickSymbol_NailGun();
    static void onClickSymbol_SplashTower();
    static void onClickSymbol_TeslaCoil();
    static void onClickSymbol_TeslaGround();
    static void onClickBuyMenu_Apply();
    static void onClickBuyMenu_Cancel();
    static void onClickMusicMute();
    static void onCLickSoundsMute();

private:
    static void onClickTowerSymbol();
    static void inactivateMenus();
    static void updateContainerTowerstats();

    static bool hasStarted;
};