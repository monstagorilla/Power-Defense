#include "GUIObject.h"

GUIObject::GUIObject(){
	this->children = std::vector<GUIObject *>();
	state = unfocused;
}

void GUIObject::draw(){

}

bool GUIObject::contains(GridPoint p){
    return p.x >= this->pos.x && p.x < this->pos.x + this->width &&
           p.y >= this->pos.y && p.y < this->pos.y + this->height;
}
