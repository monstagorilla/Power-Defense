#pragma once

#include <vector>
#include <string>
#include "GUIObject.h"


enum pathIndex {
    path_menus              = 0,
    path_menus_main         = 1,
    path_menus_main_pause   = 2,
    path_menus_buy          = 3,
    path_menus_buy_container = 4,
    path_menus_buy_container_type = 5,
    path_menus_buy_container_damage = 6,
    path_menus_buy_container_reloadTime = 7,
    path_menus_buy_container_range = 8,
    path_menus_buy_container_cost = 9,
    path_menus_buy_apply = 10,
    path_menus_tower        = 11,
    path_gamestats          = 12,
    path_mapOverlays        = 13,
    path_temp = 14,
    path_temp_towerpreview = 15
};

class GUI {
public:
    static std::vector<std::string> paths;
    static void initGUI();
    static void addGUIElement(const pathIndex path, GUIObject *object);
};