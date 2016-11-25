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

std::vector<std::string> GUI::paths = {"0", "00", "000", "01", "010", "0100", "0102", "0104", "0106", "0108", "014",
                                       "02", "1", "2", "3", "30"};

void GUI::initGUI() {
    root->children.push_back(new GUIObject()); //menus
    root->children.push_back(new GUIObject()); //gamestats
    root->children.push_back(new GUIObject()); //mapOverlays
    root->children.push_back(new GUIObject()); //temp

    addGUIElement(path_menus, new GUIObject());//menus_main
    addGUIElement(path_menus, new GUIObject());//menus_buy
    addGUIElement(path_menus, new GUIObject());//menus_tower
    addGUIElement(path_menus_buy, new Container()); //menus_tower_container

    //MAINMENU
    addGUIElement(path_menus_main, new Button("Start", {10, 0}, 5, 1, COLOR_GREEN, COLOR_RED, GUIFunctions::pause));

    //BUYMENU
    addGUIElement(path_menus_buy, new Label("SHOP", {1, 0}, 5, 1, COLOR_GREEN, nullptr));
    addGUIElement(path_menus_buy,
                  new Symbol(std::vector<std::string>{"/assets/TowerBase.png", "/assets/TowerTurret.png"}, {1, 1},
                             GUIFunctions::onClickSymbol_BasicTower));
    addGUIElement(path_menus_buy,
                  new Symbol(std::vector<std::string>{"/assets/TowerBase.png", "/assets/NailgunTurret.png"}, {2, 1},
                             GUIFunctions::onClickSymbol_NailGun)); // TODO: don't hardcode this

    //ContainerTowerStats
    addGUIElement(path_menus_buy_container, new Label("", {1, 3}, 2, 1, COLOR_WHITE, nullptr)); //title
    addGUIElement(path_menus_buy_container, new Label("Damage: ", {1, 4}, 5, 1, COLOR_WHITE, nullptr));
    addGUIElement(path_menus_buy_container, new Label("", {6, 4}, 2, 1, COLOR_WHITE, nullptr));
    addGUIElement(path_menus_buy_container, new Label("ReloadTime: ", {1, 5}, 5, 1, COLOR_WHITE, nullptr));
    addGUIElement(path_menus_buy_container, new Label("", {6, 5}, 2, 1, COLOR_WHITE, nullptr));
    addGUIElement(path_menus_buy_container, new Label("Range: ", {1, 6}, 5, 1, COLOR_WHITE, nullptr));
    addGUIElement(path_menus_buy_container, new Label("", {6, 6}, 2, 1, COLOR_WHITE, nullptr));
    addGUIElement(path_menus_buy_container, new Label("Cost: ", {1, 7}, 5, 1, COLOR_WHITE, nullptr));
    addGUIElement(path_menus_buy_container, new Label("", {6, 7}, 2, 1, COLOR_WHITE, nullptr));

    addGUIElement(path_menus_buy,
                  new Button("OK", {5, 9}, 3, 1, COLOR_GREEN, COLOR_RED, GUIFunctions::onClickBuyMenu_Apply));
    addGUIElement(path_menus_buy,
                  new Button("Cancel", {1, 9}, 3, 1, COLOR_GREEN, COLOR_RED, GUIFunctions::onClickBuyMenu_Cancel));

    //TEMP
    addGUIElement(path_temp, new Symbol(true));

    //TOWERMENU
    addGUIElement(path_menus_tower, new Button("Upgrade", {1, 9}, 5, 1, COLOR_GREEN, COLOR_RED,
                  GUIFunctions::upgradeTower));

    //GAMESTATS
    //addGUIElement(GUI::paths[path_gamestats], new Label(""))
/*
    root->getChild(paths[path_towermenu])->children.push_back(
            new Button("Upgrade", {1, 1}, 5, 1, COLOR_GREEN, COLOR_RED, GUIFunctions::upgradeTower));
    root->getChild(paths[path_towermenu])->children.push_back(
            new Button("Sell", {1, 2}, 5, 1, COLOR_GREEN, COLOR_RED, GUIFunctions::sellTower));

    root->getChild(paths[path_menus])->children.push_back(new GUIObject());//buyMenu
    root->getChild(paths[path_buymenu])->children.push_back(
            new Symbol(std::vector<std::string>{"/assets/TowerBase.png", "/assets/TowerTurret.png"}, GridPoint(8, 1)));
    //main menu
    root->getChild(paths[path_menus])->children.push_back(new GUIObject());
    root->getChild(paths[path_mainmenu])->children.push_back(
            new Button("Start", {1, 7}, 5, 1, COLOR_GREEN, COLOR_RED, GUIFunctions::startGame));
    root->getChild(paths[path_mainmenu])->children.push_back(
            new Button("End", {1, 8}, 5, 1, COLOR_GREEN, COLOR_RED, GUIFunctions::endGame));


    root->children.push_back(new GUIObject()); //stats
    root->getChild(paths[path_stats])->children.push_back(new GUIObject()); //globalstats

    root->getChild(paths[path_globalstats])->children.push_back(
            new Label("", {7, WINDOW_HEIGHT / TILE_HEIGHT - 2}, 5, 1, COLOR_WHITE,
                      GUIFunctions::setLabelPoint));//points
    root->getChild(paths[path_globalstats])->children.push_back(
            new Label("Points:", {1, WINDOW_HEIGHT / TILE_HEIGHT - 2}, 5, 1, COLOR_WHITE, nullptr));

    root->getChild(paths[path_globalstats])->children.push_back(
            new Label("", {7, WINDOW_HEIGHT / TILE_HEIGHT - 1}, 5, 1, COLOR_WHITE, GUIFunctions::setLabelMoney));//money
    root->getChild(paths[path_globalstats])->children.push_back(
            new Label("Money:", {1, WINDOW_HEIGHT / TILE_HEIGHT - 1}, 5, 1, COLOR_WHITE, nullptr));

    for (auto element: root->getChild(paths[path_globalstats])->traverse()) {
        element->isActivated = true;
    }
*/
    //activate MapOverlays and MainMenu at the beginning of the Game
    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {
            addGUIElement(path_mapOverlays,
                          new MapOverlay(Point{(float) i * TILE_WIDTH, (float) j * TILE_HEIGHT}, TILE_WIDTH,
                                         TILE_HEIGHT, GUIFunctions::onClickGround));
        }
    }

    //activate MainMenu
    for (auto element: root->getChild(paths[path_menus_main])->traverse()) {
        element->isActivated = true;
    }
}

void GUI::addGUIElement(const pathIndex path, GUIObject *object) {
    root->getChild(paths[path])->children.push_back(object);
}
