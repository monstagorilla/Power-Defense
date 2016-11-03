#include "GUI.h"
#include "Tower.h"
#include "globals.h"
#include "colors.h"
#include "Button.h"
#include "Label.h"
#include "MapOverlay.h"
#include "GUIFunctions.h"
#include "config.h"

std::vector<std::string> GUI::paths = {"0", "00", "01", "02", "1", "10", "100", "102", "2"};

void GUI::initGUI() {
    root->children.push_back(new GUIObject()); //menus
    root->getChild(paths[path_menus])->children.push_back(new GUIObject()); //towermenu
    root->getChild(paths[path_towermenu])->children.push_back(
            new Button("Upgrade", {1, 1}, 5, 1, COLOR_GREEN, COLOR_RED, GUIFunctions::upgradeTower));
    root->getChild(paths[path_towermenu])->children.push_back(
            new Button("Sell", {1, 2}, 5, 1, COLOR_GREEN, COLOR_RED, GUIFunctions::sellTower));

    root->getChild(paths[path_menus])->children.push_back(new GUIObject());//buyMenu
    root->getChild(paths[path_buymenu])->children.push_back(
            new Button("Buy", {1, 1}, 5, 1, COLOR_GREEN, COLOR_RED, GUIFunctions::addBasicTower));
    //main menu
    root->getChild(paths[path_menus])->children.push_back(new GUIObject());
    root->getChild(paths[path_mainmenu])->children.push_back(
            new Button("Start", {1, 7}, 5, 1, COLOR_GREEN, COLOR_RED, GUIFunctions::startGame));
    root->getChild(paths[path_mainmenu])->children.push_back(new Button("End", {1, 8}, 5, 1, COLOR_GREEN, COLOR_RED, GUIFunctions::endGame));


    root->children.push_back(new GUIObject()); //stats
    root->getChild(paths[path_stats])->children.push_back(new GUIObject()); //globalstats

    root->getChild(paths[path_globalstats])->children.push_back(
            new Label("", {7, WINDOW_HEIGHT / TILE_HEIGHT - 2}, 5, 1, COLOR_WHITE, GUIFunctions::setLabelPoint));//points
    root->getChild(paths[path_globalstats])->children.push_back(
            new Label("Points:", {1, WINDOW_HEIGHT / TILE_HEIGHT - 2}, 5, 1, COLOR_WHITE, nullptr));

    root->getChild(paths[path_globalstats])->children.push_back(
            new Label("", {7, WINDOW_HEIGHT / TILE_HEIGHT - 1}, 5, 1, COLOR_WHITE, GUIFunctions::setLabelMoney));//money
    root->getChild(paths[path_globalstats])->children.push_back(
            new Label("Money:", {1, WINDOW_HEIGHT / TILE_HEIGHT - 1}, 5, 1, COLOR_WHITE, nullptr));

    for (auto element: root->getChild(paths[path_globalstats])->traverse()) {
        element->isActivated = true;
    }

    //activate MapOverlays and MainMenu at the beginning of the Game
    root->children.push_back(new GUIObject);
    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {
            root->getChild(paths[path_mapOverlays])->children.push_back(
                    new MapOverlay(Point{(float) i * TILE_WIDTH, (float) j * TILE_HEIGHT}, TILE_WIDTH, TILE_HEIGHT,
                                   GUIFunctions::onClickGround));
        }
    }
    for (auto element: root->getChild(paths[path_mainmenu])->traverse()) {
        element->isActivated = true;
    }
}