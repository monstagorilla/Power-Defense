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
	this->sprites.push_back(Sprite(pos, TILE_WIDTH, TILE_WIDTH, "/assets/Enemy.png"));
}

Enemy::~Enemy() {

}

void Enemy::update() {
    pos.moveTowards(map.path[pathIndex], speed);
    if (distance(pos, map.path[pathIndex]) < 0.1) {
        pathIndex++;
		if(pathIndex == map.path.size()){
			lives -= 1;
			std::cout << "Lives left: " << lives << std::endl;
			die();
		}
    }

    for(int i = 0; i < sprites.size(); i++){
        sprites[i].pos = this->pos;
    }
    
    if(health < maxHealth){
        drawHealthbar();
    }
}

void Enemy::drawHealthbar(int width, int height, int border){
    struct rgbcolor {
        uint8_t r;
        uint8_t g;
        uint8_t b;
    };

    std::vector<rgbcolor> healthbarColors = {
        { 255, 255,   0},
        {   0, 255, 255},
        {   0, 255,   0},
        {   0,   0, 255},
        { 255,   0,   0},
        { 100,   0, 100},
    };

    auto corner = DisplayPoint{pos.x - width/2 - border, pos.y - 30 - border};
    auto inner  = DisplayPoint{pos.x - width/2, pos.y - 30}; 
    int healthscale = log10(std::max(1, maxHealth/2));
    SDL_Rect rect;
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    // Draw transparent background
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 150);
    rect.x = inner.x;
    rect.y = inner.y;
    rect.w = width;
    rect.h = height;
    SDL_RenderFillRect(renderer, &rect);
    
    // Draw thick black border
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    rect.x = inner.x-border;
    rect.y = inner.y-border;
    rect.w = border;
    rect.h = height+ border*2;
    SDL_RenderFillRect(renderer, &rect);
    rect.x = inner.x+width;
    rect.y = inner.y-border;
    rect.w = border;
    rect.h = height+border*2;
    SDL_RenderFillRect(renderer, &rect);
    rect.x = inner.x-border;
    rect.y = inner.y-border;
    rect.w = width + border*2;
    rect.h = border;
    SDL_RenderFillRect(renderer, &rect);
    rect.x = inner.x-border;
    rect.y = inner.y+height;
    rect.w = width + border*2;
    rect.h = border;
    SDL_RenderFillRect(renderer, &rect);
    
    // Draw colored healthbar
    rgbcolor c = healthbarColors[healthscale % healthbarColors.size()];
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, 255);
    rect.x = inner.x;
    rect.y = inner.y;
    rect.w = width * health/maxHealth;
    rect.h = height;
    SDL_RenderFillRect(renderer, &rect);
    
    // Draw black separating bars
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for(int i = 1; i < maxHealth/pow(10, healthscale); i++){
        rect.x = inner.x + i*width/(maxHealth/pow(10, healthscale));
        rect.y = inner.y;
        rect.w = 2;
        rect.h = height;
        SDL_RenderFillRect(renderer, &rect);
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
		if((*it)->ID == 3) {
			if(((Shot*)(*it).get())->target == this){
				(*it)->dead = true;
			}
		}
	}
}	
