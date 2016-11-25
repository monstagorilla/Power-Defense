#include "BasicShot.h"

#include "Enemy.h"
#include "util.h"

BasicShot::BasicShot(const Point pos, Tower *parent, Enemy *target, const int damage,
                     const float angle, const int speed, std::string path)
        : Shot(pos, parent, target, damage, angle) {
    this->speed = speed;
	this->sprites.push_back(Sprite(this->pos, 16, 16, path));
}

BasicShot::~BasicShot() {

}

void BasicShot::update() {
    pos.moveTowards(target->pos, speed);
    sprites[0].pos = this->pos;
    sprites[0].rotation = atan2(target->pos.y - pos.y, target->pos.x - pos.x) / M_PI * 180;
    if (distance(pos, target->pos) < speed * 2) {
        explode();
    }
}

void BasicShot::explode() {
    target->hit(*parent, damage);
    dead = true;
}
