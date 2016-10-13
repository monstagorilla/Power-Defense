#pragma once

#include <vector>

#include "globals.h"
#include "stats.h"
#include "colors.h"
#include "Tower.h"
#include "Button.h"
#include "GUIObject.h"
#include "GUIFunctions.h"

static std::string menus = "0"; //yolo or do it better??
static std::string towermenu = "00";
static std::string buymenu = "01";

void initGUI() {
    root->children.push_back(new GUIObject()); //menus
    root->getChild(menus)->children.push_back(new GUIObject()); //towermenu
    root->getChild(towermenu)->children.push_back(new Button("Upgrade", 1, 1, 5, 1, COLOR_GREEN, COLOR_RED, upgradeTower));
    root->getChild(towermenu)->children.push_back(new Button("Sell", 1, 2, 5, 1, COLOR_GREEN, COLOR_RED, upgradeTower));
    root->getChild(towermenu)->children.push_back(new Button("GodMode = on", 1, 3, 5, 1, COLOR_GREEN, COLOR_RED, upgradeTower));

    root->getChild(menus)->children.push_back(new GUIObject());//buyMenu
    root->getChild(buymenu)->children.push_back(new Button("Buy", 1, 6, 5, 1, COLOR_GREEN, COLOR_RED, addBasicTower));
}