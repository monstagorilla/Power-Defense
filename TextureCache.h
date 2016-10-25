#pragma once
#include <unordered_map>
#include <SDL2/SDL_ttf.h>

std::unordered_map<std::string, SDL_Texture*> textureCache;

SDL_Texture* getTexture(const std::string path) {
	SDL_Texture* texture;
	try{
		texture = textureCache.at(path);
	} catch(std::out_of_range) {
		SDL_Surface *surface = IMG_Load((std::string(CMAKE_SOURCE_DIR) + path).c_str());
		if (surface == NULL) {
			std::cout << "Failed to load surface " << " error : " << SDL_GetError() << std::endl;
		}
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (texture == NULL) {
			std::cout << "Failed to load texture " << path << " error : " << SDL_GetError() << std::endl;
		}
		textureCache[path] = texture;
	}
	return texture;
}
/*
//textcache
std::unordered_map < std::string, SDL_Texture*> textCache;

SDL_Texture* getText(const std::string text){
    SDL_Texture* texture;
    try{
        texture = textCache.at(text);
    }catch(std::out_of_range){

    }
}

std::unordered_map <std::string, const int size, TTF_Font> fontCache;

TTF_Font getFont(const std::string path){
    TTF_Font = font;
    try{
        font = fontCache.at(path);
    }catch{
        TTF_Font *font = TTF_OpenFont(cpath, textSize);
        if (font == NULL) {
            std::cout << SDL_GetError();
        } else {
            fonts.push_back(font);
        }
    }
    return font;
}
*/