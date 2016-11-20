#pragma once

#include <vector>
#include <string>
#include "GUIObject.h"


enum pathIndex {
    path_menus              = 0,
    path_menus_main         = 1,
    path_menus_main_pause   = 2,
    path_menus_buy          = 3,
    path_menus_tower        = 4,
    path_gamestats          = 5,
    path_mapOverlays        = 6,
};

class GUI {
public:
    static std::vector<std::string> paths;
    static void initGUI();
    static void addGUIElement(const pathIndex path, GUIObject *object);
};