#include "Sprite.h"

Sprite::Sprite(){
	pos.x = 0;
	pos.y = 0;
	rotation = 0;
	scale = 0;
	renderer = NULL;
	image = NULL;
}

Sprite::Sprite(SDL_Renderer *renderer){
	pos.x = 0;
	pos.y = 0;
	rotation = 0;
	scale = 0;
	image = 0;
	this->renderer = renderer;
}
Sprite::~Sprite(){
	
}

void Sprite::draw(){
	SDL_RenderCopy(this->renderer, this->image, NULL, NULL);	
}

void Sprite::loadImage(const char* path){
SDL_Texture* texture = NULL;
texture = IMG_LoadTexture( renderer, path );
    if ( texture == NULL )
    {
        std::cout << "Failed to load texture " << path << " error : " << SDL_GetError() << std::endl;
    }	
}
