#include <algorithm>
#include <string>

#include "Enemy.h"
#include "Sprite.h"
#include "util.h"
#include "Point.h"
#include "Map.h"
#include "config.h"
#include "globals.h"


Enemy::Enemy(Map &map, int health, float speed) : map(map) {
	this->pos = map.path[0];
	this->pathIndex = 1;
	this->health = health;
	this->maxHealth = health;
	this->speed = speed;
	ID = 1;
	this->sprites.push_back(Sprite(pos.x, pos.y, TILE_WIDTH, TILE_WIDTH, "/assets/Enemy.png"));
}

Enemy::~Enemy() {

}

void Enemy::update() {
    if (distance(pos, map.path[pathIndex]) < 0.1) {
        pathIndex++;
		if(pathIndex == map.path.size()){
			lives -= 1;
			std::cout << "Lives left: " << lives << std::endl;
			die();
		}
    }
    pos.moveTowards(map.path[pathIndex], speed);

    for(int i = 0; i < sprites.size(); i++){
        sprites[i].pos = this->pos;
    }
}

void Enemy::hit(Tower &source, int damage) {
	health -= damage;
	if(health <= 0) {
		die();
	}
}

void Enemy::die(){
	for(auto it = allGameObjects.begin(); it != allGameObjects.end(); it++){
		if((*it).get() == this){
			(*it)->dead = true;
		}
		if(((*it).get())->ID == 3) {
			if(((Shot*)(*it).get())->target == this){
				((*it).get())->dead = true;
			}
		}
	}
}	
