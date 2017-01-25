#include "BasicShot.h"

#include "Enemy.h"
#include "util.h"
#include "Cache.h"

BasicShot::BasicShot(const Point pos, Tower *parent, Enemy *target, const int damage,
                     const float angle, const int speed, std::string path)
        : Shot(pos, parent, target, damage, angle, speed) {
	this->sprites.push_back(Sprite(this->pos, 16, 16, path, true));
}

BasicShot::~BasicShot() {

}

void BasicShot::update() {
    turnTowards(target->pos, 20.0f);
    const float phi = this->angle * M_PI / 180;
    pos = this->pos + Point{(float)(speed*cos(phi)), (float)(speed*sin(phi))};
    sprites[0].pos = this->pos;
    sprites[0].rotation = angle;
    if (distance(pos, target->pos) < speed * 2) {
        explode();
    }
}

void BasicShot::explode() {
    target->hit(*parent, damage);
    dead = true;
}
