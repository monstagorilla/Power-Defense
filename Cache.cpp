#include <iostream>
#include "Cache.h"
#include "colors.h"
#include "globals.h"

std::unordered_map<std::string, SDL_Texture *> Cache::textureCache;
std::vector<std::unordered_map<std::string, SDL_Texture *>> Cache::textCache = {
        std::unordered_map<std::string, SDL_Texture *>(),
        std::unordered_map<std::string, SDL_Texture *>(),
        std::unordered_map<std::string, SDL_Texture *>()}; //TODO: dynamic size of vector
std::unordered_map<std::string, TTF_Font *> Cache::fontCache;
std::unordered_map<std::string, Mix_Chunk *> Cache::soundCache;
std::unordered_map<std::string, Mix_Music *> Cache::musicCache;

bool Cache::isSoundMuted = false;
bool Cache::isMusicMuted = false;

SDL_Texture *Cache::getTexture(const std::string path) {
    SDL_Texture *texture = nullptr;
    try {
        texture = textureCache.at(path);
    } catch (std::out_of_range) {
        SDL_Surface *surface = IMG_Load((std::string(CMAKE_SOURCE_DIR) + path).c_str());
        if (surface == nullptr) {
            std::cout << "Failed sto load surface " << " error : " << SDL_GetError() << std::endl;
        }
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture == nullptr) {
            std::cout << "Failed to load texture " << path << " error : " << SDL_GetError() << std::endl;
        }
        textureCache[path] = texture;
    }
    return texture;
}

SDL_Texture *Cache::getText(std::string text, const FontType type) {
    SDL_Texture *texture = nullptr;
    if(text == ""){
        text = " ";
    }
    try {
        texture = textCache[type].at(text);
    } catch (std::out_of_range) {
        SDL_Surface *surface = nullptr;
        switch (type) {
            case font1_green:
                surface = TTF_RenderUTF8_Blended(getFont("/fonts/Raleway-Medium.ttf"), text.c_str(), COLOR_GREEN);
                break;
            case font1_red:
                surface = TTF_RenderUTF8_Blended(getFont("/fonts/Raleway-Medium.ttf"), text.c_str(), COLOR_RED);
                break;
            case font1_white:
                surface = TTF_RenderUTF8_Blended(getFont("/fonts/Raleway-Medium.ttf"), text.c_str(), COLOR_WHITE);
                break;
        }
        if (surface == nullptr) {
            std::cout << "Failed to load surface " << " error : " << SDL_GetError() << std::endl;
        }
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        if (texture == nullptr) {
            std::cout << "Failed to load texture " << text << " error : " << SDL_GetError() << std::endl;
        } else {
            textCache[type][text] = texture;
        }
    }
    return texture;
}

TTF_Font *Cache::getFont(const std::string path) {
    TTF_Font *font = nullptr;
    try {
        font = fontCache.at(path);
    } catch (std::out_of_range) {
        font = TTF_OpenFont((std::string(CMAKE_SOURCE_DIR) + path).c_str(), 100);
        if (font == nullptr) {
            std::cout << "Failed to load font " << SDL_GetError();
        } else {
            fontCache[path] = font;
            //font == NULL !!!!!!!!!!
        }
    }
    return font;
}

Mix_Chunk *Cache::getSound(const std::string path) {
    Mix_Chunk *sound = nullptr;
    try {
        sound = soundCache.at(path);
    } catch (std::out_of_range) {
        sound = Mix_LoadWAV((std::string(CMAKE_SOURCE_DIR) + path).c_str());
        if (sound == nullptr) {
            std::cout << "Failed to load audio " << SDL_GetError();
        } else {
            soundCache[path] = sound;
        }
    }
    isSoundMuted ? Mix_VolumeChunk(sound, 0): Mix_VolumeChunk(sound, 256);
    return sound;
}

Mix_Music *Cache::getMusic(const std::string path) {
    Mix_Music *music = nullptr;
    try {
        music = musicCache.at(path);
    } catch (std::out_of_range) {
        music = Mix_LoadMUS((std::string(CMAKE_SOURCE_DIR) + path).c_str());
        Mix_VolumeMusic(64);
        if (music == nullptr) {
            std::cout << "Failed to load audio " << SDL_GetError();
        } else {
            musicCache[path] = music;
        }
    }
    return music;
}
