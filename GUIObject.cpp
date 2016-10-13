#include <iostream>
#include "GUIObject.h"

GUIObject::GUIObject() {
    this->children = std::vector<GUIObject *>();
    state = unfocused;
    isActivated = false;
    pos = GridPoint{0, 0};
    width = 0;
    height = 0;
}

void GUIObject::draw() {
    for (auto child: children) {
        child->draw();
    }
}

bool GUIObject::contains(GridPoint p) {
    return p.x >= this->pos.x && p.x < this->pos.x + this->width &&
           p.y >= this->pos.y && p.y < this->pos.y + this->height;
}

void GUIObject::activate() {
    this->isActivated = true;
    for (auto child: children) {
        child->activate();
    }
}

void GUIObject::inactivate() {
    this->isActivated = true;
    for (auto child: children) {
        child->activate();
    }
}

GUIObject *GUIObject::getChild(const std::string path) {
    if (path.length() > 0 && this->children.size() > (int) path.at(0) - 48) { //48 is the value of '0' in ASCII //
        return children[(int) path.at(0) - 48]->getChild(path.substr(1, path.length() - 1));
    } else {
        return this;
    }
}

void GUIObject::setState(const int state, const GridPoint p) {
    if (isActivated && contains(p)) {
        this->state = state;
    } else {
        for (auto child: children) {
            child->setState(state, p);
        }
    }
}

std::vector <GUIObject*> GUIObject::traverse() {
    std::vector<GUIObject*> ret = {this};
    for(auto child : children){
        auto temp = child->traverse();
        ret.insert(ret.end(), temp.begin(), temp.end());
    }
    return ret;
}