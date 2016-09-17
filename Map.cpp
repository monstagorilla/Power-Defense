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
    }
}
