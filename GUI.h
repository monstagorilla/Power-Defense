#pragma once

#include <vector>
#include <string>


enum pathIndex{
    path_menus = 0,
    path_towermenu = 1,
    path_buymenu = 2,
    path_mainmenu = 3,
    path_stats = 4,
    path_globalstats = 5,
    path_globalstats_point = 6,
    path_globalstats_money = 7,
    path_mapOverlays = 8
};

class GUI{
public:
    static std::vector<std::string> paths;
    static void initGUI();
};