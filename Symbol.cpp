#include "Symbol.h"
#include "Sprite.h"
#include "Point.h"
#include "config.h"
#include "globals.h"
#include "GUIFunctions.h"
#include "Graphics.h"
#include "Tower.h"
#include "BasicTower.h"
#include "NailGun.h"

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
        int range = 0;
        int x1 = GUIFunctions::currentPos.x;
        int y1 = GUIFunctions::currentPos.y;
        int x2 =pos.snap().x;
        int y2 =pos.snap().y;

        if (GUIFunctions::currentPos == pos.snap()) {
            switch(GUIFunctions::currentTowerType){
                case basicTower:
                    range = (int)BasicTower::stat[0].range;
                    break;
                case nailGun:
                    range = (int)NailGun::stat[0].range;
                    break;
            }
            Graphics::drawTransparentCircle(pos.displayPoint(), range);
        }
    }
}
