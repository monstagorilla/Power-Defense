#include "Point.h"
#include "Label.h"
#include "globals.h"
#include "TextOutput.h"

Label::Label(const std::string text, const GridPoint pos, int w, int h, const SDL_Color color,  void (*functptr)()): GUIObject::GUIObject() {
    this->pos = GridPoint{pos.x + MAP_WIDTH, pos.y}.center();
    width = w;
    height = h;
    this->text = text;
    this->color = color;
    isActivated = false;
    onClick = functptr;
}

Label::~Label(){

}


void Label::draw() {
    if (isActivated) {
        if(onClick){
            onClick();
        }
        TextOutput::getInstance()->drawTextAndRect(text, pos.snap() ,width, height, 8, 0, color, COLOR_BLACK);
    }
}
