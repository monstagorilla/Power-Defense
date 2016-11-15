#include "Symbol.h"
#include "Sprite.h"
#include "Point.h"
#include "config.h"

Symbol::Symbol(std::vector<std::string> paths, const GridPoint pos) : GUIObject::GUIObject() {

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
