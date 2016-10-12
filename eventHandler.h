#pragma once

#include "Point.h"
#include "globals.h"
#include "GUI.h"

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
            for (auto element: root->traverse()) {
                if (element->isActivated && element->contains(p)) {
                    element->state = focused;
                    typeFocused = Button;
                } else {
                    element->state = unfocused;
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
                    for (auto element: root->traverse()) {
                        if (element->isActivated && element->contains(p)) {
                            element->state = pressed;
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
                        currentPos = p;
                        for (auto element: root->traverse()) {
                            element->isActivated = false;
                        }
                        if(clickedTower){
                            for (auto element: root->traverse()) {
                                element->isActivated = true;
                            }
                            currentTower = clickedTower;
                        } else if(!map.isGround(p)){
                            for (auto element: root->getChild(buymenu)->traverse()) {
                                element->isActivated = true;
                            }
                        }
                    }
                case Button:
                    lastClicked = p;
                    typeClicked = typeFocused;
                    for (auto element: root->traverse()) {
                        if (element->isActivated && element->contains(p)) {
                            element->onClick();
                        }
                    }

            }
            typeClicked = Nothing;
            for (auto element: root->traverse()) {
                if (element->state == pressed) {
                    element->state = focused;
                }
            }
            break;
    }
}
