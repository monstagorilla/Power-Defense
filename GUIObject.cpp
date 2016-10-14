#include <iostream>
#include "GUIObject.h"

GUIObject::GUIObject() {
    this->children = std::vector<GUIObject *>();
    state = unfocused;
}

void GUIObject::draw() {

}

bool GUIObject::contains(GridPoint p) {
    return p.x >= this->pos.x && p.x < this->pos.x + this->width &&
           p.y >= this->pos.y && p.y < this->pos.y + this->height;
}

GUIObject *GUIObject::getChild(const std::string path) {
    if (path.length() > 0 && this->children.size() > (int) path.at(0) - 48) { //48 is the value of '0' in ASCII //
        return children[(int) path.at(0) - 48]->getChild(path.substr(1, path.length() - 1));
    } else {
        return this;
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