#include <SDL2/SDL_surface.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "Graphics.h"
#include "Point.h"
#include "globals.h"
#include "config.h"


void Graphics::drawTransparentCircle(const DisplayPoint pos, const int radius) {
    SDL_SetRenderTarget(renderer, destTextureMap);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    filledCircleRGBA(renderer, pos.x, pos.y, radius, 96, 96, 96, 100);
    circleRGBA(renderer, pos.x, pos.y, radius, 96, 96, 96, 200);
    circleRGBA(renderer, pos.x, pos.y, radius - 1, 96, 96, 96, 200);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
    SDL_SetRenderTarget(renderer, destTextureGUI);
}