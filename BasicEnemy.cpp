#include "BasicEnemy.h"

BasicEnemy::BasicEnemy(Map &map, const int level):Enemy::Enemy(map, level, 100, 3.0, 100, "/assets/Enemy.png") {

}

BasicEnemy::~BasicEnemy() {

}

void BasicEnemy::update() {
    Enemy::update();
}
