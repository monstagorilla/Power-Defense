#include <iostream>

#include "Map.h"

Map::Map(const std::string &filename) {
    tmxmap = new Tmx::Map();
    tmxmap->ParseFile(std::string(CMAKE_SOURCE_DIR) + filename);
    auto objectGroup = tmxmap->GetObjectGroup(0);
    auto object = objectGroup->GetObject(0);
    auto polyLine = object->GetPolyline();
    path = std::vector<Point>();
    for (int i = 0; i < polyLine->GetNumPoints(); i++) {
        Tmx::Point tmxpoint = polyLine->GetPoint(i);
        path.push_back(Point{tmxpoint.x, tmxpoint.y});
    }

    terrain = std::vector<std::vector<tiletype >>(tmxmap->GetWidth(),
                                                  std::vector<tiletype>(tmxmap->GetHeight(), Ground));
    auto tileLayer = tmxmap->GetTileLayer(0);
    for (int y = 0; y < tmxmap->GetHeight(); y++) {
        for (int x = 0; x < tmxmap->GetWidth(); x++) {
            unsigned tileId = tileLayer->GetTileId(x, y);
            terrain[x][y] = tileId == 14 ? Ground : Wall;
        }
    }
    sprite = Sprite({MAP_WIDTH * TILE_WIDTH / 2, WINDOW_HEIGHT / 2}, MAP_WIDTH * TILE_WIDTH, WINDOW_HEIGHT,
                    "/assets/map1.png");
    isFocused = false;
    focusedTile = {0, 0};
}

bool Map::isGround(GridPoint p) {
    if (p.x < 0 or p.y < 0 or p.x >= terrain.size() or p.y >= terrain[0].size()) {
        return true;
    } else {
        return terrain[p.x][p.y] == Ground;
    }
}

// Returns a pointer to the tower at p or nullptr if no such tower exists
Tower *Map::getTowerAt(GridPoint p) {
    for (auto &o : allGameObjects) {
        if (o->ID == 2 && o->pos.snap() == p) {
            return (Tower *) (o.get());
        }
    }
    return nullptr;
}

void Map::draw() {
    sprite.draw();
}
