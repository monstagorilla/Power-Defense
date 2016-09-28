#pragma once
#include <unordered_map>

std::unordered_map<std::string, SDL_Texture*> textureCache;

SDL_Texture* getTexture(std::string path) {
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
