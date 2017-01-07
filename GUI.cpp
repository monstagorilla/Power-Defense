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

std::vector<std::string> GUI::paths = {"a", "aa", "aaa","aab", "ab", "aba", "abaa", "abac", "abae", "abag", "abai", "ace",
                                       "ac", "b","bb", "bc","bd","be","bf", "c", "d", "da"};

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
    addGUIElement(path_menus_main, new Button("New Wave", {10, 1}, 5, 1, COLOR_GREEN, COLOR_RED, GUIFunctions::newWave));

    //BUYMENU
    addGUIElement(path_menus_buy, new Label("SHOP", {1, 0}, 5, 1, COLOR_GREEN, nullptr));
    addGUIElement(path_menus_buy,
                  new Symbol(std::vector<std::string>{"/assets/TowerBase.png", "/assets/TowerTurret.png"}, {1, 1},
                             GUIFunctions::onClickSymbol_BasicTower));
    addGUIElement(path_menus_buy,
                  new Symbol(std::vector<std::string>{"/assets/TowerBase.png", "/assets/NailgunTurret.png"}, {2, 1},
                             GUIFunctions::onClickSymbol_NailGun)); // TODO: don't hardcode this

    addGUIElement(path_menus_buy,
                  new Symbol(std::vector<std::string>{"/assets/TowerBase.png", "/assets/GrenadeTurret.png"}, {3, 1},
                             GUIFunctions::onClickSymbol_SplashTower));

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
    addGUIElement(path_temp, new Symbol(true, true)); //TODO: needing different solution because of rendering Symbols not into mapTexture

    //TOWERMENU
    addGUIElement(path_menus_tower, new Button("Upgrade", {1, 9}, 5, 1, COLOR_GREEN, COLOR_RED,
                                               GUIFunctions::upgradeTower));

    //GAMESTATS
    addGUIElement(path_gamestats, new Symbol(std::vector<std::string>{"/assets/Gold.png"}, {1 - MAP_WIDTH, MAP_HEIGHT + 1}, nullptr));
    addGUIElement(path_gamestats, new Label("", {2 - MAP_WIDTH, MAP_HEIGHT + 1}, 5, 1, COLOR_WHITE, GUIFunctions::setLabelMoney));
    addGUIElement(path_gamestats, new Label("", {5 - MAP_WIDTH, MAP_HEIGHT + 1}, 5, 1, COLOR_WHITE, GUIFunctions::setLabelPoint));
    addGUIElement(path_gamestats, new Label("", {13 , 2}, 5, 1, COLOR_WHITE, GUIFunctions::setLabelWaveCount));
    addGUIElement(path_gamestats, new Label("", {10 - MAP_WIDTH,MAP_HEIGHT + 1}, 5, 1, COLOR_WHITE, GUIFunctions::setLabelLevel));
    addGUIElement(path_gamestats, new Label(std::to_string(gamestats.lives), {16 - MAP_WIDTH,MAP_HEIGHT + 1}, 5, 1, COLOR_WHITE, GUIFunctions::setLabelLives));
    addGUIElement(path_gamestats, new Symbol(std::vector<std::string>{"/assets/Doodads.png"}, {4 - MAP_WIDTH, MAP_HEIGHT + 1}, nullptr));
    addGUIElement(path_gamestats, new Label("Next Wave: ", {10 , 2}, 5, 1, COLOR_WHITE, nullptr));
    addGUIElement(path_gamestats, new Label("Level: ", {8 - MAP_WIDTH, MAP_HEIGHT + 1}, 5, 1, COLOR_WHITE, nullptr));
    addGUIElement(path_gamestats, new Symbol(std::vector<std::string>{"/assets/heart.png"}, {15 - MAP_WIDTH, MAP_HEIGHT + 1}, nullptr));


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
    root->getChild(paths[path_menus_main_newWave])->isActivated = false;
    //activate Stats
    for (auto element: root->getChild(paths[path_gamestats])->traverse()) {
        element->isActivated = true;
    }
}

void GUI::addGUIElement(const pathIndex path, GUIObject *object) {
    root->getChild(paths[path])->children.push_back(object);
}
