#include "GUIObject.h"

GUIObject::GUIObject(){
	this->children = std::vector<GUIObject *>();
	state = unfocused;
}

void GUIObject::draw(){

}
