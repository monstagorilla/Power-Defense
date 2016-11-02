#include "Point.h"
#include "MapOverlay.h"
#include "config.h"
#include "globals.h"

#include <iostream>

MapOverlay::MapOverlay(const Point pos, const int width, const int height, void(*onClick) ()) : GUIObject::GUIObject() {
    this->pos = pos;
    this->width = width;
    this->height = height;
    this->onClick = onClick;
}

MapOverlay::~MapOverlay() {

}

void MapOverlay::draw() {
    if (state == focused) {
        SDL_Rect rect;
        DisplayPoint corner = pos.snap().upperLeft();
        rect.x = corner.x;
        rect.y = corner.y;
        rect.w = TILE_WIDTH;
        rect.h = TILE_HEIGHT;
        SDL_RenderDrawRect(renderer, &rect);
    }
}

void MapOverlay::update() {
    if (mousePos.snap() == pos.snap() || clickedPos.snap() == pos.snap()) {
        state = focused;
    } else {
        state = unfocused;
    }
    if(mousePos.snap() == pos.snap() && mouseRelease){
        if(this->onClick){
            std::cout << "scurrr"<< std::endl;
            this->onClick();
        }
    }
}
