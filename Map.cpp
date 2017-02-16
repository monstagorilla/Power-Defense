#include <iostream>
#include <vector>

#include "Point.h"
#include "Sprite.h"
#include "Tower.h"
#include "Map.h"
#include "globals.h"
#include "config.h"
#include "Cache.h"

Map::Map() {
    tmxmap = nullptr;
    terrain = std::vector<std::vector<tiletype >>();
    isFocused = false;
    focusedTile = GridPoint();
    path = std::vector<Point>();

}

Map::Map(const std::string &filename) {
    tmxmap = new Tmx::Map();
    tmxmap->ParseFile(std::string(CMAKE_SOURCE_DIR) + filename);
    auto objectGroup = tmxmap->GetObjectGroup(0);
    auto object = objectGroup->GetObject(0);
    auto polyLine = object->GetPolyline();
    path = std::vector<Point>();
    for (int i = 0; i < polyLine->GetNumPoints(); i++) {
        Tmx::Point tmxpoint = polyLine->GetPoint(i);
        path.push_back(Point{tmxpoint.x + MAP_OFFSET_X, tmxpoint.y + MAP_OFFSET_Y});
    }

    terrain = std::vector<std::vector<tiletype >>(tmxmap->GetWidth(),
                                                  std::vector<tiletype>(tmxmap->GetHeight(), Ground));
    auto tileLayer = tmxmap->GetTileLayer(0);
    SDL_Rect srcRect;
    srcRect.w = TILE_WIDTH;
    srcRect.h = TILE_HEIGHT;
    SDL_Rect destRect;
    destRect.w = TILE_WIDTH;
    destRect.h = TILE_HEIGHT;
    SDL_Texture *srcTexture = Cache::getTexture("/assets/GreenTiles.png");
    destTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBX8888, SDL_TEXTUREACCESS_TARGET,
                                    TILE_WIDTH * MAP_WIDTH, TILE_HEIGHT * MAP_HEIGHT);
    SDL_SetRenderTarget(renderer, destTexture);
    for (int y = 0; y < tmxmap->GetHeight(); y++) {
        for (int x = 0; x < tmxmap->GetWidth(); x++) {
            switch (tileLayer->GetTileId(x, y)) {
                case 12:
                case 11:
                case 10:
                case 7:
                case 3:
                case 2:
                    terrain[x][y] = Ground;
                    break;
                default:
                    terrain[x][y] = Wall;
            }
            srcRect.x = tileLayer->GetTileId(x, y) % 5 * TILE_WIDTH;
            srcRect.y = (int) (tileLayer->GetTileId(x, y) / 5) * TILE_HEIGHT;
            destRect.x = (int) (((double) x - 0.5) * TILE_WIDTH);
            destRect.y = (int) (((double) y - 0.5) * TILE_HEIGHT);
            SDL_RenderCopyEx(renderer, srcTexture, &srcRect, &destRect, 0, NULL, SDL_FLIP_NONE);
        }
    }
    destRect.x = 10 * TILE_WIDTH;
    destRect.y = 5 * TILE_HEIGHT;
    SDL_RenderCopyEx(renderer, Cache::getTexture("/assets/Doodads.png"), NULL, &destRect, 0, NULL, SDL_FLIP_NONE);

    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(srcTexture);

    sprite = Sprite({TILE_WIDTH * MAP_WIDTH / 2, TILE_HEIGHT * MAP_HEIGHT / 2}, TILE_WIDTH * MAP_WIDTH,
                    TILE_HEIGHT * MAP_HEIGHT, destTexture, true);
    isFocused = false;
    focusedTile = {0, 0};
}

Map::~Map() {

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
        if ((o->ID == 2 || o->ID == 5 )&& o->pos.snap() == p) {
            return (Tower *) (o.get());
        }
    }
    return nullptr;
}

void Map::draw() {
    sprite.draw();
}

int Map::getHeight() {
    return tmxmap->GetHeight();
}

int Map::getWidth() {
    return tmxmap->GetWidth();
}
