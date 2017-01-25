#pragma once

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <iostream>

#include "Point.h"

class Sprite {
public:
    Sprite();
    Sprite(const Point pos, const int width, const int height, const std::string path, const bool renderInMap);
    Sprite(const Point pos, const int width, const int height, SDL_Texture* texture, const bool renderInMap);
    virtual ~Sprite();
    void draw();

    SDL_Texture *texture;
    Point pos;
    int width;
    int height;

    float rotation;
    float scale;
private:
    bool renderInMap;
};
