#pragma once

#include "tmxparser/Tmx.h"
#include "Point.h"
#include "Sprite.h"
#include "Tower.h"
#include "config.h"
#include "globals.h"

enum tiletype {
    Ground = 0,
    Wall   = 1,
};

class Map {
    private:
        Tmx::Map* tmxmap;
        std::vector<std::vector<tiletype>> terrain;
        Sprite sprite;
        
    public:
        Map(){};
        Map(const std::string& filename);
        ~Map(){}
        bool isFocused;
        GridPoint focusedTile;
        std::vector<Point> path;
        int getHeight(){ return tmxmap->GetHeight(); };
        int getWidth (){ return tmxmap->GetWidth();  };
        bool isGround(GridPoint p);
        Tower* getTowerAt(GridPoint p);
        void draw();
};
