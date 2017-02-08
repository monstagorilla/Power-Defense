#include "Point.h"
#include "Label.h"
#include "globals.h"
#include "TextOutput.h"
#include "config.h"

Label::Label(const eGUI identifier, const std::string text, const GridPoint pos, const int w, const int h, const SDL_Color color, void (*functptr)(),const bool isActivated,const bool renderInMap, const bool leftAligned)
        : GUIObject::GUIObject(identifier, renderInMap) {
    this->pos = GridPoint{pos.x + MAP_WIDTH, pos.y}.center();
    width = w;
    height = h;
    this->text = text;
    this->color = color;
    this->isActivated = false;
    onClick = functptr;
    this->leftAligned = leftAligned;
}

Label::~Label() {

}


void Label::draw() {
    if (isActivated) {
        if (onClick != nullptr) { //TODO: perhaps separate logic and drawing
            onClick();
        }
        if(renderInMap){
            SDL_SetRenderTarget(renderer, destTextureMap);
        }else{
            SDL_SetRenderTarget(renderer, destTextureGUI);
        }
        if(leftAligned) {//TODO: different drawing depending on alignment
            TextOutput::drawText(text, pos.snap(), 8, font1_white); //TODO: using class member color
        }else{
            TextOutput::drawText(text, pos.snap(), 8, font1_white);
        }
    }
}
