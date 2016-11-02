#pragma once

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <iostream>

//#include "util.h"

#include "Point.h"
class Sprite {
public:
    Sprite();
    Sprite(const Point pos, const int width, const int height, std::string path);
    ~Sprite();
    void draw();

    SDL_Texture *texture;
    Point pos;
    int width;
    int height;

    float rotation;
    float scale;
};
