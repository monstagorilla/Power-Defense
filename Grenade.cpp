#include "Grenade.h"
#include "util.h"
#include "Point.h"
#include "Enemy.h"
#include "globals.h"

Grenade::Grenade(const Point pos, Tower *parent, Enemy *target, const int damage, const float angle, const float speed) : Shot::Shot(pos,
                                                                                                                  parent,
                                                                                                                  target,
                                                                                                                  damage,
                                                                                                                  angle,
                                                                                                                  speed) {
    explosionRad = 100;
    destPos = target->pos;
    this->sprites.push_back(Sprite(this->pos, 16, 16, "/assets/Grenade.png", true));
}

Grenade::~Grenade() {

}

void Grenade::update() {
    turnTowards(destPos, 8.0f);
    const float phi = this->angle * M_PI / 180;
    pos = this->pos + Point{(float) (speed * cos(phi)), (float) (speed * sin(phi))};
    sprites[0].pos = this->pos;
    sprites[0].rotation = angle;
    if (distance(pos, destPos) < speed * 2) {
        explode();
    }
}

void Grenade::explode() {
    for (int i = 0; i < allGameObjects.size(); i++) {
        if (allGameObjects[i]->ID == 1 && distance(allGameObjects[i]->pos, pos) <= explosionRad) {
            ((Enemy *) allGameObjects[i].get())->hit(*parent, (int) (damage - distance(allGameObjects[i]->pos, pos) /
                                                                             explosionRad));
        }
    }
    dead = true;
}
