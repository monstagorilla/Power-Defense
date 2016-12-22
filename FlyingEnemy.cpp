#include "FlyingEnemy.h"
#include "globals.h"
#include "util.h"
#include "GUIFunctions.h"
#include "Map.h"

FlyingEnemy::FlyingEnemy(Map &map, const int level, const Point pos) : Enemy::Enemy(map, level, 10, 3.0, 100,
                                                                                    "/assets/Enemy.png") {
    this->pos = pos;
}

FlyingEnemy::~FlyingEnemy() {

}

void FlyingEnemy::update() {
    const auto targetPos = map.path.back();
    pos.moveTowards(targetPos, getStat().speed);
    if (distance(pos, targetPos) < 0.1) {
        if (lives == 0) {
            GUIFunctions::endGame();
            std::cout << "GAME OVER" << std::endl;
        } else {
            lives--;
            std::cout << "Lives left: " << lives << std::endl;
        }
        die();
    }

    for (int i = 0; i < sprites.size(); i++) {
        sprites[i].pos = this->pos;
        sprites[i].rotation = atan2(targetPos.y - this->pos.y, targetPos.x - this->pos.x) * 180 / M_PI;
    }
}