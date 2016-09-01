#include "Sprite.h"

Sprite::Sprite(){
	pos.x = 0;
	pos.y = 0;
	rotation = 0;
	scale = 0;
	renderer = NULL;
	image = NULL;
}

Sprite::Sprite(const SDL_Renderer *renderer){
	pos.x = 0;
	pos.y = 0;
	rotation = 0;
	scale = 0;
	image = 0;
	this.renderer = renderer;
}
Sprite::~Sprite({
	
})

void Sprite::draw(){
	SDL_RenderCopy(this.renderer, this.image, NULL, NULL);	
}

void Sprite::loadImage(const string path){
SDL_Texturee* texture = NULL;
texture = IMG_LoadTexture( renderer, path );
    if ( texture == nullptr )
    {
        std::cout << "Failed to load texture " << str << " error : " << SDL_GetError() << std::endl;
    }	
}
