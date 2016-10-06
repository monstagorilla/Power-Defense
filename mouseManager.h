#pragma once

#include "Point.h"
#include "globals.h"
#include "textboxes.h"

static bool isClicked = false;

static void mouseHandler(const Point pos, SDL_Event &ev) {
    int xPos = pos.x / TILE_WIDTH;
    int yPos = pos.y / TILE_HEIGHT;

    //display rect on the focused map tile
    if (xPos <= MAP_WIDTH && !map.isGround(xPos, yPos)) {
        SDL_Rect rect;
        rect.x = xPos * TILE_WIDTH;
        rect.y = yPos * TILE_HEIGHT;
        rect.w = TILE_WIDTH;
        rect.h = TILE_HEIGHT;
        SDL_RenderDrawRect(renderer, &rect);
    } else if (xPos > MAP_WIDTH) { //focus button
        for (auto child: root->children) {
            if (child->isActivated && xPos >= (int) child->pos.x / TILE_WIDTH &&
                xPos < (int) child->pos.x / TILE_WIDTH + child->width / TILE_WIDTH &&
                (int) child->pos.y / TILE_HEIGHT == yPos) {
                child->state = focused;
            } else {
                child->state = unfocused;
            }
        }
    }

    //managing mouse clicks
    if (ev.button.state == SDL_PRESSED) {
        isClicked = true;
        for (auto child: root->children) {
            if (child->isActivated && xPos >= (int) child->pos.x / TILE_WIDTH &&
                xPos < (int) child->pos.x / TILE_WIDTH + child->width / TILE_WIDTH &&
                (int) child->pos.y / TILE_HEIGHT == yPos) {
                child->state = pressed;
            }
        }
    } else if (isClicked) {
        isClicked = false;

        //click left
        if (ev.button.button == SDL_BUTTON_LEFT) {
            //map
            for (auto child:root->children) {
                child->state = unfocused;
            }
            if (xPos <= MAP_WIDTH) {
                Tower *actualTower = NULL;
                for (auto *object : allGameObjects) {
                    if ((int) object->pos.x == xPos && (int) object->pos.y == yPos) {
                        actualTower = (Tower *) object;
                        break;
                    }
                }
                for (auto child: root->children) {
                    if (actualTower != NULL) {
                        child->isActivated = true;
                    } else {
                        child->isActivated = false;
                    }
                }
            }
        }
    }
}
