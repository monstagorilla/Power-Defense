#include "GUIObject.h"

GUIObject::GUIObject(){
	this->children = std::vector<GUIObject *>();
}

void GUIObject::draw(){
	if(isActivated){
		for (auto child : children){
			child->draw();
		}
	}
}
