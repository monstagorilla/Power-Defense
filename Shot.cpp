#include "Shot.h"
#include "globals.h"
#include "Enemy.h"
#include "math.h"

#include <algorithm>

Shot::Shot(Point pos, Tower* parent, Enemy* target) {
	this->pos = pos;
	this->target = target;
	this->parent = parent;
	this->speed  = 3.5;
	this->damage = 10;
	ID = 3;
	this->sprites.push_back(Sprite(this->pos.x, this->pos.y, 16, 16, "/assets/Shot.png"));
	target->shots.push_back(this);
}

Shot::~Shot() {
}

void Shot::update() {
	pos.moveTowards(target->pos, speed);	
	sprites[0].pos = this->pos;
	sprites[0].rotation = atan2(target->pos.y - pos.y, target->pos.x - pos.x)/M_PI * 180;
	if(distance(pos, target->pos) < speed*2){
		explode();
	}
}

void Shot::explode() {
	target->hit(*parent, damage);
	dead = true;
}
