#include <stdlib.h>
#include <cmath>

#include "Lightning.h"
#include "Point.h"

#include "globals.h"
#include "config.h"
#include "colors.h"

static float envelope(const float s) {
    return sin(s*M_PI);
}

Lightning::Lightning(const Point start, const Point end, const int duration):
    end(end), duration(duration * FRAMES_PER_SECOND), GameObject(start) {
    Point n((end-pos).y, (pos-end).x);
    float o = 0.0;
    for(float s = 0.0; s < 1.0; s += 0.01){
        o += 0.03*(drand48() - 0.5);
        points.push_back(end * s + pos * (1.0f - s) + n * o*envelope(s));
    }
}

void Lightning::draw() {
    SDL_SetRenderDrawColor(renderer, COLOR_LIGHTNING.r, COLOR_LIGHTNING.g, COLOR_LIGHTNING.b, 255);
    SDL_RenderDrawLine(renderer, pos.x, pos.y, points[0].x, points[0].y);
    for(int i = 0; i < points.size() - 1; i++){
        SDL_RenderDrawLine(renderer, points[i].x, points[i].y, points[i+1].x, points[i+1].y);
    }
    SDL_RenderDrawLine(renderer, points.back().x, points.back().y, end.x, end.y);
}

void Lightning::update() {
    this->duration--;
    if(this->duration <= 0) {
        dead = true;
    }
}

Lightning::~Lightning(){}

