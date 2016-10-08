#pragma once

#include "Point.h"
#include "globals.h"
#include "textboxes.h"

enum Clickable {
    Nothing,
    MapTile,
    Button,
};

static Clickable typeFocused = Nothing;
static Clickable typeClicked = Nothing;
static GridPoint lastClicked = {0, 0};

static void handleEvent(SDL_Event &ev){
    GridPoint p;
    switch (ev.type) {

    case SDL_MOUSEMOTION:
        p = DisplayPoint{ ev.motion.x, ev.motion.y }.snap();
        typeFocused = Nothing;
        if (p.x <= MAP_WIDTH){
            if(!map.isGround(p)) {
                map.isFocused = true;
                map.focusedTile = p;
                typeFocused = MapTile;
            } else {
                map.isFocused = false;
            }
        }
        for (auto child: root->children) {
            if (child->isActivated && child->contains(p)) {
                child->state = focused;
                typeFocused = Button;
            } else {
                child->state = unfocused;
            }
        }
        break;

    case SDL_MOUSEBUTTONDOWN:
        p = DisplayPoint { ev.button.x, ev.button.y }.snap();
        switch (typeFocused) {
        case Nothing:
            break;
        case MapTile:
        case Button:
            lastClicked = p;
            typeClicked = typeFocused;
            for (auto child: root->children) {
                if (child->isActivated && child->contains(p)) {
                    child->state = pressed;
                }
            }
        }
        break;

    case SDL_MOUSEBUTTONUP:
        p = DisplayPoint { ev.button.x, ev.button.y }.snap();
        switch (typeClicked) {
        case Nothing:
            break;
        case MapTile:
            if(p == lastClicked) {
                Tower* clickedTower = map.getTowerAt(p);
                if(clickedTower){
                    for (auto child: root->children) {
                        child->isActivated = true;
                    }
                } else {
                    for (auto child: root->children) {
                        child->isActivated = false;
                    }
                }
            }
        case Button:
            lastClicked = p;
            typeClicked = typeFocused;
        }
        typeClicked = Nothing;
        for (auto child: root->children) {
            if (child->state == pressed) {
                child->state = focused;
            }
        }
        break;
    }
}
