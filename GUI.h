#pragma once

#include <vector>

#include "globals.h"
#include "stats.h"
#include "colors.h"
#include "Tower.h"
#include "Button.h"
#include "GUIObject.h"
#include "GUIFunctions.h"
#include "Label.h"

std::string path_menus = "0"; //yolo or do it better??
std::string path_towermenu = "00";
std::string path_buymenu = "01";

std::string path_stats = "1";
std::string path_globalstats = "10";
std::string path_globalstats_point = "100";
std::string path_globalstats_money = "102";

void initGUI() {
    root->children.push_back(new GUIObject()); //menus
    root->getChild(path_menus)->children.push_back(new GUIObject()); //towermenu
    root->getChild(path_towermenu)->children.push_back(
            new Button("Upgrade", 1, 1, 5, 1, COLOR_GREEN, COLOR_RED, upgradeTower));
    root->getChild(path_towermenu)->children.push_back(
            new Button("Sell", 1, 2, 5, 1, COLOR_GREEN, COLOR_RED, upgradeTower));
    root->getChild(path_towermenu)->children.push_back(
            new Button("GodMode = on", 1, 3, 5, 1, COLOR_GREEN, COLOR_RED, upgradeTower));

    root->getChild(path_menus)->children.push_back(new GUIObject());//buyMenu
    root->getChild(path_buymenu)->children.push_back(
            new Button("Buy", 1, 6, 5, 1, COLOR_GREEN, COLOR_RED, addBasicTower));

    root->children.push_back(new GUIObject()); //stats
    root->getChild(path_stats)->children.push_back(new GUIObject()); //globalstats
    root->getChild(path_globalstats)->children.push_back(new Label("", 7, WINDOW_HEIGHT/TILE_HEIGHT - 2, 5, 1, COLOR_WHITE, setLabelPoint));//points
    root->getChild(path_globalstats)->children.push_back(new Label("Points:", 1, WINDOW_HEIGHT / TILE_HEIGHT - 2, 5, 1, COLOR_WHITE,
                                                                   nullptr));

    root->getChild(path_globalstats)->children.push_back(new Label("", 7, WINDOW_HEIGHT/TILE_HEIGHT - 1, 5, 1, COLOR_WHITE,setLabelMoney));//money
    root->getChild(path_globalstats)->children.push_back(new Label("Money:", 1, WINDOW_HEIGHT / TILE_HEIGHT - 1, 5, 1, COLOR_WHITE,
                                                                   nullptr));


    for (auto element: root->getChild(path_globalstats)->traverse()) {
        element->isActivated = true;
    }

}