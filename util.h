#pragma once

#include <math.h>
#include <iostream>
#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Point.h"

extern SDL_Renderer *renderer;

static float distance(const Point a, const Point b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

static bool loadImage(std::vector<std::string> paths, std::vector<SDL_Texture *> textures) {
	if (paths.size() != textures.size()) {
		return false;
	}

	for (int i = 0; i < textures.size(); i++) {
		SDL_Surface *surface = IMG_Load((std::string(CMAKE_SOURCE_DIR) + paths[i]).c_str());
		if (surface == NULL) {
			std::cout << "Failed to load surface " << " error : " << SDL_GetError() << std::endl;
		}
		textures[i] = SDL_CreateTextureFromSurface(renderer, surface);
		if (textures[i] == NULL) {
			std::cout << "Failed to load texture " << i << " error : " << SDL_GetError() << std::endl;
			return false;
		}
	}
	return true;
}