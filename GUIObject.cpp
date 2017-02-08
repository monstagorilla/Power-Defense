#include <iostream>
#include <SDL2/SDL_mixer.h>

#include "Point.h"
#include "GUIObject.h"
#include "globals.h"
#include "Cache.h"

GUIObject::GUIObject(const eGUI identifier, const bool renderInMap) {
    this->identifier = identifier;
    children = std::vector<GUIObject *>();
    state = unfocused;
    isActivated = false;
    pos = Point(0, 0);
    width = 1;
    height = 1;
    text = "";
    color = {0, 0, 0, 0};
    onClick = nullptr;
    this->renderInMap = renderInMap;
}

GUIObject::~GUIObject() {

}

void GUIObject::update() {
    if (isActivated) {
        state = unfocused;
        if (mousePos.snap().x >= pos.snap().x && mousePos.snap().x < pos.snap().x + width &&
            mousePos.snap().y >= pos.snap().y && mousePos.snap().y < pos.snap().y + height) {
            if (mouseRelease) {
                if (onClick != nullptr) {
                    onClick();
                    Mix_PlayChannel(-1, Cache::getSound("/audio/mouse_up.wav"), 0);
                }
                state = focused;
            } else if (isCLicked) {
                state = pressed;
                Mix_PlayChannel(-1, Cache::getSound("/audio/mouse_down.wav"), 0);
            } else {
                state = focused;
            }
        }
    }
}

void GUIObject::draw() {

}


GUIObject *GUIObject::getChild(const eGUI identifier) {
    if(this->identifier == identifier){
        return this;
    }
    for (auto element: children) {
        if(element->identifier == identifier){
            return element;
        }else if(element->getChild(identifier)) {
            return element->getChild(identifier);
        }
    }
    return nullptr;
}

std::vector<GUIObject *> GUIObject::traverse() {
    std::vector<GUIObject *> ret = {this};
    for (auto child : children) {
        auto temp = child->traverse();
        ret.insert(ret.end(), temp.begin(), temp.end());
    }
    return ret;
}
