#include "Sprite.h"
#include "globals.h"
#include "TextureCache.h"

Sprite::Sprite(const Point pos, const int width, const int height, std::string path){
    this->pos = pos;
    this->width = width;
    this->height = height;
	rotation = 0;
	scale = 0;
    this->texture = getTexture(path);
}

Sprite::~Sprite(){
	
}

void Sprite::draw(){
    SDL_Rect destRect;
    destRect.x = this->pos.x - this->width/2;
    destRect.y = this->pos.y - this->height/2;
    destRect.w = this->width;
    destRect.h = this->height;

    SDL_RenderCopyEx(renderer, this->texture, NULL, &destRect, rotation, NULL, SDL_FLIP_NONE);
}
