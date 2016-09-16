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

Sprite::Sprite(const int x, const int y, const int width, const int height,  const string path, SDL_Renderer *renderer){
	this->pos.x = x;
    this->pos.y = y;
    this->width = width;
    this->height = height;
	rotation = 0;
	scale = 0;
    texture = NULL;
    this->renderer = renderer;
    loadImage(path);
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

void Sprite::loadImage(const string path){
    SDL_Surface* surface = NULL;
    surface = IMG_Load(path.c_str());
    if ( surface == NULL )
    {
        std::cout << "Failed to load surface "  << " error : " << SDL_GetError() << std::endl;
    }

    SDL_Texture *texture = NULL;
    texture = SDL_CreateTextureFromSurface(this->renderer, surface);
    if ( texture == NULL )
    {
        std::cout << "Failed to load texture "  << " error : " << SDL_GetError() << std::endl;
    }
    this->texture = texture;
}
