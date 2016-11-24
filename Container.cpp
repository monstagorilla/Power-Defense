#include "Container.h"
#include "globals.h"
#include "config.h"
#include "colors.h"

Container::Container() : GUIObject::GUIObject() {
}

Container::~Container() {

}

void Container::update() {

}

void Container::draw() {
    //TODO: make static behaviour / only one time init
    if(isActivated) {
        int left = STATS_WIDTH;
        int right = 0;
        int top = WINDOW_HEIGHT / TILE_HEIGHT;
        int bottom = 0;
        DisplayPoint topLeft;
        for (auto object: traverse()) {
            if(object == this){
                continue;
            }
            if (object->pos.snap().x - MAP_WIDTH < left) {
                left = object->pos.snap().x - MAP_WIDTH;
                topLeft.x = object->pos.displayPoint().x;
            }
            if (object->pos.snap().x + object->width - MAP_WIDTH > right) {
                right = object->pos.snap().x + object->width - MAP_WIDTH;
            }
            if (object->pos.snap().y < top) {
                top = object->pos.snap().y;
                topLeft.y = object->pos.displayPoint().y;
            }
            if (object->pos.snap().y + object->height > bottom) {
                bottom = object->pos.snap().y + object->height;
            }
        }
        SDL_Rect rect;
        rect.x = (int) (topLeft.x -  TILE_WIDTH/2.0);
        rect.y = (int)(topLeft.y  -TILE_HEIGHT/2.0);
        rect.w = (right - left) * TILE_WIDTH;
        rect.h = (bottom - top) * TILE_HEIGHT;

        SDL_SetRenderDrawColor(renderer, 255,255,255,255);
        SDL_RenderDrawRect(renderer, &rect);
    }
}
