#include "Point.h"
#include "Label.h"
#include "globals.h"
#include "TextOutput.h"
#include "config.h"

Label::Label(const std::string text, const GridPoint pos, int w, int h, const SDL_Color color, void (*functptr)())
        : GUIObject::GUIObject() {
    this->pos = GridPoint{pos.x + MAP_WIDTH, pos.y}.center();
    width = w;
    height = h;
    this->text = text;
    this->color = color;
    isActivated = false;
    onClick = functptr;
}

Label::~Label() {

}


void Label::draw() {
    if (isActivated) {
        if (onClick != nullptr) {
            onClick();
        }
        TextOutput::drawText(text, pos.snap(), 8, font1_white);
    }
}
