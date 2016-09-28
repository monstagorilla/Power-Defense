#include "Sprite.h"
#include "globals.h"

Sprite::Sprite(const int x, const int y, const int width, const int height,  SDL_Texture* texture){
	this->pos.x = x;
    this->pos.y = y;
    this->width = width;
    this->height = height;
	rotation = 0;
	scale = 0;
    this->texture = texture;
}

Sprite::~Sprite(){
	
}

void Sprite::draw(){
    SDL_Rect destRect;
    destRect.x = this->pos.x;
    destRect.y = this->pos.y;
    destRect.w = this->width;
    destRect.h = this->height;

	SDL_RenderCopyEx(renderer, this->texture, NULL, &destRect, rotation, NULL, SDL_FLIP_NONE);
}
