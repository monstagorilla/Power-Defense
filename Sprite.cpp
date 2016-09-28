#include "Sprite.h"
#include "globals.h"
#include "TextureCache.h"

extern std::unordered_map<std::string, SDL_Texture*> textureCache;

Sprite::Sprite(const int x, const int y, const int width, const int height, std::string path){
	this->pos.x = x;
    this->pos.y = y;
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
    destRect.x = this->pos.x;
    destRect.y = this->pos.y;
    destRect.w = this->width;
    destRect.h = this->height;

	SDL_RenderCopyEx(renderer, this->texture, NULL, &destRect, rotation, NULL, SDL_FLIP_NONE);
}
