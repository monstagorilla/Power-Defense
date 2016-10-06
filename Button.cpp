#include "Button.h"
#include "colors.h"
#include "TextOutput.h"

Button::Button(std::string text, int x, int y, int w, int h, const SDL_Color color, const SDL_Color colorPressed) {
    pos.x = TILE_WIDTH * (x + MAP_WIDTH);
    pos.y = TILE_HEIGHT * y;
    width = TILE_WIDTH * w;
    height = TILE_HEIGHT * h;
    this->text = text;
    this->color = color;
    this->colorPressed = colorPressed;
    isActivated = false;
}

Button::~Button() {

}

void Button::draw() {
    if (isActivated) {
        auto foregroundColor = color;
        auto backgroundColor = color;
        if (state == focused) {
            foregroundColor = colorPressed;
        } else if (state == pressed) {
            foregroundColor = colorPressed;
            backgroundColor = colorPressed;
        }
        TextOutput::getInstance()->drawTextAndRect(text, pos.x, pos.y, width, height, 8, 0, foregroundColor,
                                                   backgroundColor);
        for (auto child: children) {
            child->draw();
        }
    }
}
