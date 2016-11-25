#include "Point.h"
#include "Shot.h"
#include "Tower.h"
#include "globals.h"
#include "Enemy.h"
#include "Sprite.h"
#include "util.h"

#include <algorithm>
#include <math.h>

Shot::Shot(const Point pos, Tower* parent, Enemy* target, const int damage, const float angle, const int speed) {
	this->pos = pos;
	this->target = target;
	this->parent = parent;
	this->damage = damage;
    this->speed = speed;
    this->angle = angle;
	ID = 3;
	target->shots.push_back(this);
}

Shot::~Shot() {
}

void Shot::update() {

}

void Shot::turnTowards(const Point target, const float turnAngle){
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

void Shot::explode() {

}
