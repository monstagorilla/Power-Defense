#include "BasicShot.h"

#include "Enemy.h"
#include "util.h"

BasicShot::BasicShot(const Point pos, Tower *parent, Enemy *target, const int damage,
                     const float angle, const int speed, std::string path)
        : Shot(pos, parent, target, damage) {
    this->speed = speed;
    this->angle = angle;
	this->sprites.push_back(Sprite(this->pos, 16, 16, path));
}

BasicShot::~BasicShot() {

}

void BasicShot::update() {
    turnTowards(target->pos, 8.0f);
    const float phi = this->angle * M_PI / 180;
    pos = this->pos + Point{speed*cos(phi), speed*sin(phi)};
    sprites[0].pos = this->pos;
    sprites[0].rotation = angle;
    if (distance(pos, target->pos) < speed * 2) {
        explode();
    }
}

void BasicShot::turnTowards(const Point target, const float turnAngle){
    const float targetAngle = atan2(target.y - pos.y, target.x - pos.x) / M_PI * 180;
    const float diffAngle   = abs(targetAngle - angle) > 180.0f
            ? targetAngle - angle - 360.0f
            : targetAngle - angle;
    if(abs(diffAngle) < turnAngle){
        angle = targetAngle;
    } else {
        angle += turnAngle * diffAngle/abs(diffAngle);
    }
}

void BasicShot::explode() {
    target->hit(*parent, damage);
    dead = true;
}
