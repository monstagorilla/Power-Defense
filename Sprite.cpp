#include "Sprite.h"

Sprite::Sprite(){
	pos.x = 0;
	pos.y = 0;
    width = 0;
    height = 0;
	rotation = 0;
	scale = 0;
	renderer = NULL;
	texture = NULL;
}

Sprite::Sprite(SDL_Renderer *renderer){
	pos.x = 0;
	pos.y = 0;
    width = 0;
    height = 0;
	rotation = 0;
	scale = 0;
	texture = 0;
	this->renderer = renderer;
}

Sprite::~Sprite(){
	
}

void Sprite::draw(){
    SDL_Rect destRect;
    destRect.x = this->pos.x;
    destRect.y = this->pos.y;
    destRect.w = this->width;
    destRect.h = this->height;

	SDL_RenderCopyEx(this->renderer, this->texture, NULL, &destRect, rotation, NULL, SDL_FLIP_NONE);
}

void Sprite::loadImage(string path){
    SDL_Surface* surface = NULL;
    surface = IMG_Load(path.c_str());
    if ( surface == NULL )
    {
        std::cout << "Failed to load surface "  << " error : " << SDL_GetError() << std::endl;
    }

    SDL_Texture *texture = NULL;
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if ( texture == NULL )
    {
        std::cout << "Failed to load texture "  << " error : " << SDL_GetError() << std::endl;
    }
    this->texture = texture;
}
