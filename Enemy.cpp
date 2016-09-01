#include "Enemy.h"
#include "util.h"
#include "Point.h"

Enemy::Enemy(std::vector<Point> path, int health, float speed){
    this->path 	    = path;
    this->pos        = path[0];
    this->pathIndex  = 1;
    this->health     = health;
    this->maxHealth  = health;
    this->speed      = speed;
}

void Enemy::update(){
    if(distance(pos, path[pathIndex]) < 0.1){
        pathIndex++;
    }
    pos.moveTowards(path[pathIndex], speed);
}

void Enemy::hit(Tower& source, int damage){
    health -= damage;
}
