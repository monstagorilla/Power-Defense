#include <iostream>

#include "Point.h"
#include "GUIObject.h"

GUIObject::GUIObject() {
    children = std::vector<GUIObject *>();
    state = unfocused;
    isActivated = false;
    pos = Point(0,0);
    width = 0;
    height = 0;
    text = "";
    color = {0, 0, 0, 0};
    onClick = nullptr;
}

GUIObject::~GUIObject() {

}

void GUIObject::update() {

}

void GUIObject::draw() {

}

bool GUIObject::contains(GridPoint p) {
    return p.x >= this->pos.snap().x && p.x < this->pos.snap().x + this->width &&
           p.y >= this->pos.snap().y && p.y < this->pos.snap().y + this->height;
}

GUIObject *GUIObject::getChild(const std::string path) {
    if (path.length() > 0 && this->children.size() > (int) path.at(0) - 48) { //48 is the value of '0' in ASCII //
        return children[(int) path.at(0) - 48]->getChild(path.substr(1, path.length() - 1));
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
