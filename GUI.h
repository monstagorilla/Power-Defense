#pragma once

#include <vector>
#include <string>
#include "GUIObject.h"


enum pathIndex {
    path_menus              = 0,
    path_menus_main         = 1,
    path_menus_main_pause   = 2,
    path_menus_main_newWave   = 3,
    path_menus_buy          = 4,
    path_menus_buy_container = 5,
    path_menus_buy_container_type = 6,
    path_menus_buy_container_damage = 7,
    path_menus_buy_container_reloadTime = 8,
    path_menus_buy_container_range = 9,
    path_menus_buy_container_cost = 10,
    path_menus_buy_apply = 11,
    path_menus_tower        = 12,
    path_gamestats          = 13,
    path_gamestats_money = 14,
    path_gamestats_points = 15,
    path_gamestats_waveCount = 16,
    path_mapOverlays        = 17,
    path_temp = 18,
    path_temp_towerpreview = 19,
};

class GUI {
public:
    static std::vector<std::string> paths;
    static void initGUI();
    static void addGUIElement(const pathIndex path, GUIObject *object);
};