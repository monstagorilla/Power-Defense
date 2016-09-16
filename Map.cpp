#include "Map.h"

Map::Map(std::string& filename) {
    tmxmap = Tmx::Map();
    tmxmap.ParseFile(std::string(CMAKE_SOURCE_DIR) + filename);
}
