#include "Wave.h"
#include "WaveItem.h"
#include "globals.h"
#include "BasicEnemy.h"
#include "FlyingEnemy.h"
#include "Point.h"

Wave::Wave(const uint32_t startTime,std::vector<WaveItem> items) {
    this->items = std::vector<WaveItem>(items);
    this->startTime = startTime;
    isEmpty = false;
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
