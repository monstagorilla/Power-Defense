#pragma once

#include <unordered_map>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <vector>
#include <string>
#include "font.h"

class Cache {
public:
    static SDL_Texture *getTexture(const std::string path);
    static SDL_Texture *getText(std::string text, const FontType type);
    static TTF_Font* getFont(const std::string path);
    static Mix_Chunk* getSound (const std::string path);
    static Mix_Music* getMusic(const std::string path);

    static bool isSoundMuted;
    static bool isMusicMuted;
private:
    static std::unordered_map<std::string, SDL_Texture *> textureCache;
    static std::vector <std::unordered_map<std::string, SDL_Texture *>> textCache;
    static std::unordered_map<std::string, TTF_Font*> fontCache;
    static std::unordered_map<std::string, Mix_Chunk*> soundCache;

    static std::unordered_map<std::string, Mix_Music*> musicCache;
};
