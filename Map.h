#pragma once

//#include <tmxparser/Tmx.h>
#include "tmxparser/Tmx.h"
#include "config.h"
#include "globals.h"

enum tiletype {
    Ground = 0,
    Wall = 1,
};

class GridPoint;

class Point;

class Tower;

class Sprite;

class Map {
private:
    Tmx::Map *tmxmap;
    std::vector<std::vector<tiletype>> terrain;
    Sprite sprite;

public:
    Map();

    Map(const std::string &filename);

    ~Map();

    bool isFocused;
    GridPoint focusedTile;
    std::vector<Point> path;

    int getHeight();

    int getWidth();

    bool isGround(GridPoint p);

    Tower *getTowerAt(GridPoint p);

    void draw();
};
