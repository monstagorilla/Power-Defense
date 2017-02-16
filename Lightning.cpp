#include <stdlib.h>

#include "Lightning.h"
#include "Point.h"

#include "globals.h"
#include "config.h"
#include "colors.h"

Lightning::Lightning(const Point start, const Point end, int duration):
    end(end), duration(duration * FRAMES_PER_SECOND), GameObject(start) {
    srand48(0);
    for(float s = 0.0; s < 1.0; s += 0.0001){
        points.push_back(pos * s + end * (1.0f - s) + Point(drand48() - 0.5, drand48() - 0.5));
    }
}

void Lightning::draw() {
    SDL_SetRenderDrawColor(renderer, COLOR_LIGHTNING.r, COLOR_LIGHTNING.g, COLOR_LIGHTNING.b, 255);
    SDL_RenderDrawLine(renderer, pos.x, pos.y, end.x, end.y);
}

void Lightning::update() {
    this->duration--;
    if(this->duration <= 0) {
        dead = true;
    }
}

Lightning::~Lightning(){}

