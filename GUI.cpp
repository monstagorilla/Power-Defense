#include <vector>
#include <string>

#include "GUI.h"
#include "Tower.h"
#include "globals.h"
#include "colors.h"
#include "Button.h"
#include "Label.h"
#include "MapOverlay.h"
#include "GUIFunctions.h"
#include "Symbol.h"
#include "config.h"
#include "Container.h"
#include "gamestats.h"
#include "TeslaGround.h"
#include "TeslaCoil.h"


void GUI::initGUI() {
    //MENUS
    addGUIObject(root, new GUIObject(menus));
    addGUIObject(menus, new GUIObject(menus_main));
    addGUIObject(menus_main, new Button(buttonStart, "Start", {10, 0}, 5, 1, COLOR_GREEN, COLOR_RED, GUIFunctions::pause));
    addGUIObject(menus_main, new Button(buttonNewWave, "New Wave", {10, 1}, 5, 1, COLOR_GREEN, COLOR_RED, GUIFunctions::newWave));
    addGUIObject(menus_main, new Button(buttonFX, "Fx Off", {10, 2}, 2, 1, COLOR_GREEN, COLOR_RED, GUIFunctions::onCLickSoundsMute));
    addGUIObject(menus_main, new Button(buttonMusic, "Music Off", {12, 2}, 3, 1, COLOR_GREEN, COLOR_RED, GUIFunctions::onClickMusicMute));

    addGUIObject(menus, new GUIObject(menus_buy));
    addGUIObject(menus_buy, new Label(lblBuyTitleMain, "SHOP", {1, 0}, 5, 1, COLOR_GREEN, nullptr));
    addGUIObject(menus_buy, new Symbol(symbolBasicTower, std::vector<std::string>{"/assets/TowerBase.png", "/assets/TowerTurret.png"}, {1, 1}, GUIFunctions::onClickSymbol_BasicTower));
    addGUIObject(menus_buy, new Symbol(symbolNailGun, std::vector<std::string>{"/assets/TowerBase.png", "/assets/NailgunTurret.png"}, {2, 1}, GUIFunctions::onClickSymbol_NailGun));
    addGUIObject(menus_buy, new Symbol(symbolSplashTower, std::vector<std::string>{"/assets/TowerBase.png", "/assets/GrenadeTurret.png"}, {3, 1}, GUIFunctions::onClickSymbol_SplashTower));
    addGUIObject(menus_buy, new Symbol(symbolTeslaCoil, TeslaCoil::stat[0].paths, {4, 1}, GUIFunctions::onClickSymbol_TeslaCoil));
    addGUIObject(menus_buy, new Symbol(symbolTeslaGround, TeslaGround::stat[0].paths, {5, 1}, GUIFunctions::onClickSymbol_TeslaGround));

    addGUIObject(menus_buy, new Container(menus_buy_container));
    addGUIObject(menus_buy_container, new Label(lblBuyTitleMain, "", {1, 3}, 4, 1, COLOR_WHITE, nullptr)); //title
    addGUIObject(menus_buy_container, new Label(lblBuyTitleDamage, "Damage: ", {1, 4}, 5, 1, COLOR_WHITE, nullptr));
    addGUIObject(menus_buy_container, new Label(lblBuyDamage, "", {5, 4}, 4, 1, COLOR_WHITE, nullptr));
    addGUIObject(menus_buy_container, new Label(lblBuyTitleReloadTime, "ReloadTime: ", {1, 5}, 5, 1, COLOR_WHITE, nullptr));
    addGUIObject(menus_buy_container, new Label(lblBuyReloadTime,"", {5, 5}, 4, 1, COLOR_WHITE, nullptr));
    addGUIObject(menus_buy_container, new Label(lblBuyTitleRange, "Range: ", {1, 6}, 5, 1, COLOR_WHITE, nullptr));
    addGUIObject(menus_buy_container, new Label(lblBuyRange, "", {5, 6}, 4, 1, COLOR_WHITE, nullptr));
    addGUIObject(menus_buy_container, new Label(lblBuyTitleCost, "Cost: ", {1, 7}, 5, 1, COLOR_WHITE, nullptr));
    addGUIObject(menus_buy_container, new Label(lblBuyCost, "", {5, 7}, 4, 1, COLOR_WHITE, nullptr));
    addGUIObject(menus_buy, new Button(buttonBuyOK,"OK", {5, 9}, 3, 1, COLOR_GREEN, COLOR_RED, GUIFunctions::onClickBuyMenu_Apply));
    addGUIObject(menus_buy, new Button(buttonBuyCancel,"Cancel", {1, 9}, 3, 1, COLOR_GREEN, COLOR_RED, GUIFunctions::onClickBuyMenu_Cancel));

    addGUIObject(menus, new GUIObject(menus_tower));
    addGUIObject(menus_tower, new Button(buttonTowerUpgrade,"Upgrade", {1, 9}, 5, 1, COLOR_GREEN, COLOR_RED, GUIFunctions::upgradeTower));

    //TEMP
    addGUIObject(root, new GUIObject(temp));
    addGUIObject(temp, new Symbol(symbolTemp, true, true)); //TODO: needing different solution because of rendering Symbols not into mapTexture

    //GAMESTATS
    addGUIObject(root, new GUIObject(mainStats));
    addGUIObject(mainStats,
                 new Symbol(symbolGold,std::vector<std::string>{"/assets/Gold.png"}, {-MAP_WIDTH, MAP_HEIGHT + 1}, nullptr));
    addGUIObject(mainStats,
                 new Label(lblMoney, "", {1 - MAP_WIDTH, MAP_HEIGHT + 1}, 5, 1, COLOR_WHITE, GUIFunctions::setLabelMoney));
    addGUIObject(mainStats,
                 new Label(lblPoint, "", {4 - MAP_WIDTH, MAP_HEIGHT + 1}, 5, 1, COLOR_WHITE, GUIFunctions::setLabelPoint));
    addGUIObject(mainStats,
                 new Label(lblWaveCount,"", {12 - MAP_WIDTH, MAP_HEIGHT + 1}, 5, 1, COLOR_WHITE, GUIFunctions::setLabelWaveCount));
    addGUIObject(mainStats,
                 new Label(lblLevel, "", {8 - MAP_WIDTH, MAP_HEIGHT + 1}, 5, 1, COLOR_WHITE, GUIFunctions::setLabelLevel));
    addGUIObject(mainStats,
                 new Label(lblLives, std::to_string(gamestats.lives), {15 - MAP_WIDTH, MAP_HEIGHT + 1}, 5, 1, COLOR_WHITE,
                           GUIFunctions::setLabelLives));
    addGUIObject(mainStats,
                 new Symbol(symbolPoints, std::vector<std::string>{"/assets/Doodads.png"}, {3 - MAP_WIDTH, MAP_HEIGHT + 1},
                            nullptr));
    addGUIObject(mainStats,
                 new Label(lblNextWave, "Next Wave: ", {9 - MAP_WIDTH, MAP_HEIGHT + 1}, 5, 1, COLOR_WHITE, nullptr));
    addGUIObject(mainStats, new Label(lblWave, "Wave: ", {6 - MAP_WIDTH, MAP_HEIGHT + 1}, 5, 1, COLOR_WHITE, nullptr));
    addGUIObject(mainStats,
                 new Symbol(symbolLives, std::vector<std::string>{"/assets/heart.png"}, {14 - MAP_WIDTH, MAP_HEIGHT + 1}, nullptr));


    //activate MapOverlays and MainMenu at the beginning of the Game
    addGUIObject(root, new GUIObject(mapOverlays));
    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {
            addGUIObject(mapOverlays, new MapOverlay(Point{(float) i * TILE_WIDTH, (float) j * TILE_HEIGHT}, TILE_WIDTH,
                                         TILE_HEIGHT, GUIFunctions::onClickGround));
        }
    }

    //activate MainMenu
    for (auto element: root->getChild(menus_main)->traverse()) {
        element->isActivated = true;
    }
    root->getChild(buttonNewWave)->isActivated = false;
    //activate Stats
    for (auto element: root->getChild(mainStats)->traverse()) {
        element->isActivated = true;
    }
}

void GUI::addGUIObject(GUIObject *parent, GUIObject *newObject) {
    if (parent) {
        parent->children.push_back(newObject);
    } else {
        std::cout << "parent object does not exist!" << std::endl;
    }
}

void GUI::addGUIObject(eGUI identifier, GUIObject *newObject) {
    if (root->getChild(identifier)) {
        addGUIObject(root->getChild(identifier), newObject);
    }
}