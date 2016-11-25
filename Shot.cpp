#include "Point.h"
#include "Shot.h"
#include "Tower.h"
#include "globals.h"
#include "Enemy.h"
#include "Sprite.h"
#include "util.h"

#include <algorithm>
#include <math.h>

Shot::Shot(const Point pos, Tower* parent, Enemy* target, const int damage, const float angle) {
	this->pos = pos;
	this->target = target;
	this->parent = parent;
	this->damage = damage;
	ID = 3;
    this->angle = angle;
	target->shots.push_back(this);
}

Shot::~Shot() {
}

void Shot::update() {

}
