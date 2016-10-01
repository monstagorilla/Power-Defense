#include "Shot.h"
#include "globals.h"
#include "Enemy.h"
#include "math.h"

Shot::Shot(const int x, const int y, const int direction) {
	this->pos.x = x;
	this->pos.y = y;
	this->direction = direction;
	this->speed = 1;
	ID = 3;
	this->sprites.push_back(Sprite(this->pos.x, this->pos.y, 16, 16, "/assets/Shot.png"));
}

Shot::~Shot() {

}

void Shot::update() {
	Enemy *nearest = NULL;
	int shortestDist = 10000000; //YOLOLOLOL
	for (int i = 0; i < allGameObjects.size(); i++) {
		if (allGameObjects[i]->ID == 1 && distance(allGameObjects[i]->pos, this->pos) < shortestDist) {
			nearest = (Enemy *) allGameObjects[i];
			shortestDist = distance(allGameObjects[i]->pos, this->pos);
		}
	}
	direction = atan2(nearest->pos.y- this->pos.y , nearest->pos.x - this->pos.x)/M_PI*180;
	this->pos.x += speed * cos(direction * M_PI / 180);
	this->pos.y += speed * sin(direction * M_PI / 180);
	sprites[0].pos = this->pos;
}

