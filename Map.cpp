#include <iostream>

#include "Map.h"

Map::Map(const std::string &filename) {
    tmxmap = Tmx::Map();
    tmxmap.ParseFile(std::string(CMAKE_SOURCE_DIR) + filename);
    auto objectGroup = tmxmap.GetObjectGroup(0);
    auto object = objectGroup->GetObject(0);
    auto polyLine = object->GetPolyline();
    path = std::vector<Point>();
    for (int i = 0; i < polyLine->GetNumPoints(); i++) {
        Tmx::Point tmxpoint = polyLine->GetPoint(i);
        path.push_back(Point{tmxpoint.x, tmxpoint.y});
        std::cout << tmxpoint.x << ", " << tmxpoint.y << std::endl;
    }
    
    terrain = std::vector<std::vector<tiletype>>(tmxmap.GetWidth(),
            std::vector<tiletype>(tmxmap.GetHeight(), Ground));
    auto tileLayer = tmxmap.GetTileLayer(0);
    for(int y = 0; y < tmxmap.GetHeight(); y++){
        for(int x = 0; x < tmxmap.GetWidth(); x++){
            unsigned tileId = tileLayer->GetTileId(x, y);
            terrain[x][y] = tileId == 14 ? Ground : Wall;
            std::cout << terrain[x][y] << " ";
        }   
        std::cout << std::endl;
    }
	sprite = Sprite(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, WINDOW_WIDTH, WINDOW_HEIGHT, "/assets/map1.png");
}

bool Map::isGround(int x, int y) {
    if(x < 0 or y < 0 or x >= terrain.size() or y >= terrain[0].size()){
        return true;
    } else {
        return terrain[x][y] == Ground;
    }
}

void Map::draw(){
	sprite.draw();
}
