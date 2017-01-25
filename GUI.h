#pragma once

#include <vector>
#include <string>
#include "GUIObject.h"


enum pathIndex {
    path_menus              = 0,
    path_menus_main         = 1,
    path_menus_main_pause   = 2,
    path_menus_main_newWave   = 3,
    path_menus_main_muteSounds = 4,
    path_menus_main_muteMusic = 5,
    path_menus_buy          = 6,
    path_menus_buy_container = 7,
    path_menus_buy_container_type = 8,
    path_menus_buy_container_damage = 9,
    path_menus_buy_container_reloadTime = 10,
    path_menus_buy_container_range = 11,
    path_menus_buy_container_cost = 12,
    path_menus_buy_apply = 13,
    path_menus_tower        = 14,
    path_gamestats          = 15,
    path_gamestats_money = 16,
    path_gamestats_points = 17,
    path_gamestats_waveCount = 18,
    path_gamestats_level = 19,
    path_gamestats_lives = 20,
    path_mapOverlays        = 21,
    path_temp = 22,
    path_temp_towerpreview = 23,
};

class GUI {
public:
    static std::vector<std::string> paths;
    static void initGUI();
    static void addGUIElement(const pathIndex path, GUIObject *object);
};