#include "Enemy.h"
#include "util.h"
#include "Point.h"

Enemy::Enemy(Map map, int health, float speed){
    this->map        = map;
    this->pos        = map.path[0];
    this->pathIndex  = 1;
    this->health     = health;
    this->maxHealth  = health;
    this->speed      = speed;
}

void Enemy::update(){
    if(distance(pos, map.path[pathIndex]) < 0.1){
        pathIndex++;
    }
    pos.moveTowards(map.path[pathIndex], speed);
}

void Enemy::hit(Tower& source, int damage){
    health -= damage;
}
