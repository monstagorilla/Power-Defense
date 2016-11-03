#include <SDL2/SDL.h>

#include "Point.h"
#include "Button.h"
#include "TextOutput.h"
#include "config.h"

Button::Button(const std::string text, const GridPoint pos, const int w, const int h, const SDL_Color color,
               const SDL_Color colorPressed, void (*onCLick)()) : GUIObject::GUIObject() {
    this->pos = GridPoint(pos.x + MAP_WIDTH, pos.y).center();
    width = w;
    height = h;
    this->text = text;
    this->color = color;
    this->colorPressed = colorPressed;
    isActivated = false;
    this->onClick = onCLick;
}

Button::~Button() {

}

void Button::draw() {
    if (isActivated) {
        //TODO: find more elegant solution
        auto foregroundColor = color;
        auto fontType = font1_green;
        if (state == focused) {
            foregroundColor = colorPressed;
        } else if (state == pressed) {
            foregroundColor = colorPressed;
            fontType = font1_red;
        }
        TextOutput::drawTextAndRect(text, pos.snap(), width, height, 8, fontType, foregroundColor);
    }
}

void Button::update() {
    if (isActivated) {
        state = unfocused;
        if (mousePos.snap().x >= pos.snap().x && mousePos.snap().x < pos.snap().x + width &&
            mousePos.snap().y >= pos.snap().y && mousePos.snap().y < pos.snap().y + height) {
            if (mouseRelease) {
                if (onClick) {
                    onClick();
                }
                state = focused;
            } else if (isCLicked) {
                state = pressed;
            } else {
                state = focused;
            }
        }
    }
}
