#include "Button.h"
#include "colors.h"
#include "TextOutput.h"

Button::Button(std::string text, int x, int y, int w, int h, const SDL_Color color, const SDL_Color colorPressed, void (*onCLick)()): GUIObject::GUIObject() {
    pos.x = (x + MAP_WIDTH);
    pos.y = y;
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
        GUIObject::draw();
        auto foregroundColor = color;
        auto backgroundColor = color;
        if (state == focused) {
            foregroundColor = colorPressed;
        } else if (state == pressed) {
            foregroundColor = colorPressed;
            backgroundColor = colorPressed;
        }
        TextOutput::getInstance()->drawTextAndRect(text, pos, width, height, 8, 0, foregroundColor,
                                                   backgroundColor);
    }
}
