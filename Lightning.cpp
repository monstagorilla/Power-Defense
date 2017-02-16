#include <stdlib.h>
#include <cmath>

#include "Lightning.h"
#include "Point.h"
#include "Cache.h"

#include "globals.h"
#include "config.h"
#include "colors.h"

static float envelope(const float s) {
    return sin(s*M_PI);
}

static void draw_particle(const Point pos, SDL_Texture* particle){
    SDL_Rect destRect;
    destRect.x = (int) pos.x - 1;
    destRect.y = (int) pos.y - 1;
    destRect.w = 3;
    destRect.h = 3;
    SDL_RenderCopyEx(renderer, particle, NULL, &destRect, 0, NULL, SDL_FLIP_NONE);
}

Lightning::Lightning(const Point start, const Point end, const float duration):
    end(end), duration((int)(duration * FRAMES_PER_SECOND)), GameObject(start) {
    Point n((end-pos).y, (pos-end).x);
    float o = 0.0;
    for(float s = 0.0; s < 1.0; s += 0.01){
        o += 0.05*(drand48() - 0.5);
        points.push_back(end * s + pos * (1.0f - s) + n * o*envelope(s));
    }
}

void Lightning::draw() {
    auto particle = Cache::getTexture("/assets/LightningParticle.png");
    SDL_SetTextureBlendMode(particle, SDL_BLENDMODE_ADD);
    SDL_SetRenderTarget(renderer, destTextureMap);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    for(auto point : points){
        draw_particle(point, particle);
    }
}

void Lightning::update() {
    this->duration--;
    Point n((end-pos).y, (pos-end).x);
    float o = 0.0;
    for(int i = 0; i < points.size(); i++){
        float s = (float)i/points.size();
        o += 0.05*(drand48() - 0.5);
        points[i] = end * s + pos * (1.0f - s) + n * o*envelope(s);
    }
    if(this->duration <= 0) {
        dead = true;
    }
}

Lightning::~Lightning(){}

