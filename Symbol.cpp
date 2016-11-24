#include "Symbol.h"
#include "Sprite.h"
#include "Point.h"
#include "config.h"
#include "globals.h"

Symbol::Symbol() : GUIObject::GUIObject() {

}

Symbol::Symbol(std::vector<std::string> paths, const GridPoint pos, void (*onCLick)()) : GUIObject::GUIObject() {
    this->onClick = onCLick;
    isActivated = false;
    this->pos = GridPoint(pos.x + MAP_WIDTH, pos.y).center();
    for (auto element: paths) {
        sprites.push_back(Sprite(GridPoint(MAP_WIDTH + pos.x, pos.y).center(), TILE_WIDTH, TILE_HEIGHT, element));
    }
}

Symbol::~Symbol() {

}

void Symbol::update() {
    GUIObject::update(); //TODO: use abstraction to reduce redundancy
}

void Symbol::draw() {
    if (isActivated) {
        for (auto element: sprites) {
            element.draw();
        }
    }
}
