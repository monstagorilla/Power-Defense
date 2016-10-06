#include "Button.h"
#include "colors.h"
#include "TextOutput.h"

Button::Button(std::string text, int x, int y, int w, int h, const SDL_Color color, const SDL_Color colorPressed) {
	pos.x = x;
	pos.y = y;
	width = w;
	height = h;
	this->text = text;
	this->color = color;
	this->colorPressed = colorPressed;
	state = unfocused;
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
			foregroundColor = COLOR_BLACK;
			backgroundColor = colorPressed;
		}
		TextOutput::getInstance()->drawTextAndRect(text, TILE_WIDTH * (pos.x + MAP_WIDTH),
												   TILE_HEIGHT * (pos.y), TILE_WIDTH * width,
												   TILE_HEIGHT * height, 8, 0, foregroundColor, backgroundColor);
        for(auto child: children){
            child->draw();
        }
	}
}
