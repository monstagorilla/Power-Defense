#include "Enemy.h"
#include "util.h"
Enemy::Enemy(){
    // TODO: implement this
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
