#include <vector>

#include "Point.h"
#include "Sprite.h"
#include "GameObject.h"

GameObject::GameObject() {
    pos.x = 0;
    pos.y = 0;
    sprites = std::vector<Sprite> ();
    ID = -1;
    dead = false;
}
GameObject::GameObject(const Point pos) {
    this->pos.x = pos.x;
    this->pos.y = pos.y;
    sprites = std::vector<Sprite> ();
    ID = -1;
    dead = false;
}


GameObject::~GameObject() {

}

void GameObject::update() {

}

