#pragma once

#include "Point.h"
#include "globals.h"
#include "textboxes.h"

static void handleEvent(SDL_Event &ev){
    switch (ev.type) {
    case SDL_MOUSEMOTION:
        GridPoint p = DisplayPoint{ ev.motion.x, ev.motion.y }.snap();
        if (p.x <= MAP_WIDTH && !map.isGround(p)) {
            map.isFocussed = true;
            map.focussedTile = p;
        } else {
            map.isFocussed = false;
        }
        if (p.x > MAP_WIDTH) {
            for (auto child: root->children) {
                if (child->isActivated && p.x >= (int) child->pos.x / TILE_WIDTH &&
                    p.x < (int) child->pos.x / TILE_WIDTH + child->width / TILE_WIDTH &&
                    (int) child->pos.y / TILE_HEIGHT == p.y) {
                    child->state = focused;
                } else {
                    child->state = unfocused;
                }
            }
        }
    }
}
