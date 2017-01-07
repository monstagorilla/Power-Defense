#include "Wave.h"
#include "WaveItem.h"
#include "globals.h"
#include "BasicEnemy.h"
#include "FlyingEnemy.h"
#include "Point.h"
#include "config.h"

Wave::Wave(const uint32_t startTime,std::vector<WaveItem> items) {
    for(auto element: items){
        this->items.push_back(element);
        this->items.back().startTime = element.startTime * FRAMES_PER_SECOND;
    }
    this->startTime = startTime;
    isEmpty = false;
    length = (items.back().startTime + TIME_TO_PREPARE) * FRAMES_PER_SECOND;

}

Wave::~Wave() {

}

void Wave::update() {
    while (!items.empty() && startTime + items.front().startTime <= gameLoopCounter) {
        if (items.empty()) {
            isEmpty = true;
            return;
        }
        switch (items.front().type) {
            case basicEnemy:
                allGameObjects.push_back(std::make_unique<BasicEnemy>(map, items.front().level));
                break;
            case flyingEnemy:
                allGameObjects.push_back(std::make_unique<FlyingEnemy>(map, items.front().level, Point(20, 0))); //TODO: write getPos function
                break;
        }
        items.erase(items.begin());
    }
}
