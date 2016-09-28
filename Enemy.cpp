#include <string>

#include "Enemy.h"
#include "Sprite.h"
#include "util.h"
#include "Point.h"
#include "Map.h"
#include "config.h"


Enemy::Enemy(Map &map, int health, float speed) : map(map) {
	this->pos = map.path[0];
	this->pathIndex = 1;
	this->health = health;
	this->maxHealth = health;
	this->speed = speed;
	ID = 1;
	for (int i = 0; i < textures.size(); i++) {
		this->sprites.push_back(Sprite(pos.x, pos.y, TILE_WIDTH, TILE_WIDTH, textures[i]));
	}
}

Enemy::~Enemy() {

}

void Enemy::update() {
	if (distance(pos, map.path[pathIndex]) < 0.1) {
		pathIndex++;
	}
	pos.moveTowards(map.path[pathIndex], speed);

	for (int i = 0; i < sprites.size(); i++) {
		sprites[i].pos = this->pos;
	}
}

void Enemy::hit(Tower &source, int damage) {
	health -= damage;
}
