#pragma once

#include <unordered_map>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <string>
#include "font.h"

class Cache {
public:
    static SDL_Texture *getTexture(const std::string path);
    static SDL_Texture *getText(const std::string text, const FontType type);
    static TTF_Font* getFont(const std::string path);

private:
    static std::unordered_map<std::string, SDL_Texture *> textureCache;
    static std::vector <std::unordered_map<std::string, SDL_Texture *>> textCache;
    static std::unordered_map<std::string, TTF_Font*> fontCache;
};
