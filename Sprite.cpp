#include "Point.h"
#include "globals.h"
#include "Cache.h"
#include "Sprite.h"
#include "util.h"

Sprite::Sprite() {
    pos = Point();
    texture = nullptr;
    width = 0;
    height = 0;

    rotation = 0;
    scale = 0;
}


Sprite::Sprite(const Point pos, const int width, const int height, std::string path) {
    this->pos = Point(pos.x, pos.y);
    this->width = width;
    this->height = height;
    rotation = 0;
    scale = 0;
    this->texture = Cache::getTexture(path);
}

Sprite::~Sprite() {

}

void Sprite::draw() {
    SDL_Rect destRect;
    destRect.x = (int) this->pos.x - this->width / 2;
    destRect.y = (int) this->pos.y - this->height / 2;
    destRect.w = this->width;
    destRect.h = this->height;

    SDL_RenderCopyEx(renderer, this->texture, NULL, &destRect, rotation, NULL, SDL_FLIP_NONE);
}
