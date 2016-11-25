#include <iostream>

#include "Point.h"
#include "GUIObject.h"
#include "globals.h"

GUIObject::GUIObject() {
    children = std::vector<GUIObject *>();
    state = unfocused;
    isActivated = false;
    pos = Point(0,0);
    width = 1;
    height = 1;
    text = "";
    color = {0, 0, 0, 0};
    onClick = nullptr;
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
                }
                state = focused;
            } else if (isCLicked) {
                state = pressed;
            } else {
                state = focused;
            }
        }
    }
}

void GUIObject::draw() {

}

bool GUIObject::contains(GridPoint p) {
    return p.x >= this->pos.snap().x && p.x < this->pos.snap().x + this->width &&
           p.y >= this->pos.snap().y && p.y < this->pos.snap().y + this->height;
}

GUIObject *GUIObject::getChild(const std::string path) {
    if (path.length() > 0 && this->children.size() > (int) path.at(0) - 97) { //48 is the value of '0' in ASCII //
        return children[(int) path.at(0) - 97]->getChild(path.substr(1, path.length() - 1));
    } else {
        return this;
    }
}

std::vector<GUIObject *> GUIObject::traverse() {
    std::vector<GUIObject *> ret = {this};
    for (auto child : children) {
        auto temp = child->traverse();
        ret.insert(ret.end(), temp.begin(), temp.end());
    }
    return ret;
}
