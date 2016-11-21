#include "Point.h"
#include "Label.h"
#include "globals.h"
#include "TextOutput.h"
#include "config.h"

Label::Label(const std::string text, const GridPoint pos, const int w, const int h, const SDL_Color color, void (*functptr)(), const bool leftAligned)
        : GUIObject::GUIObject() {
    this->pos = GridPoint{pos.x + MAP_WIDTH, pos.y}.center();
    width = w;
    height = h;
    this->text = text;
    this->color = color;
    isActivated = false;
    onClick = functptr;
    this->leftAligned = leftAligned;
}

Label::~Label() {

}


void Label::draw() {
    if (isActivated) {
        if (onClick != nullptr) {
            onClick();
        }
        if(leftAligned) {
            TextOutput::drawText(text, pos.snap(), 8, font1_white); //TODO: using class member color
        }else{
            TextOutput::drawText(text, pos.snap(), 8, font1_white);
        }
    }
}
