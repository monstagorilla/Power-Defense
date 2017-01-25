#pragma once

#include "tmxparser/Tmx.h"

enum tiletype {
    Ground = 0,
    Wall = 1,
};

class GridPoint;

class Point;

class Tower;

#include "Sprite.h"

class Map {
public:
    Map();
    Map(const std::string &filename);
    virtual ~Map();

    int getHeight();
    int getWidth();
    bool isGround(GridPoint p);
    Tower *getTowerAt(GridPoint p);
    void draw();

    bool isFocused;
    GridPoint focusedTile;
    std::vector<Point> path;

private:
    Tmx::Map *tmxmap;
    std::vector<std::vector<tiletype>> terrain;
    Sprite sprite;
    SDL_Texture* destTexture;
};
