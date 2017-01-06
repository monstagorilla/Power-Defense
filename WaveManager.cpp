#include <iostream>
#include "WaveManager.h"
#include "EnemyType.h"
#include "Wave.h"
#include "globals.h"

WaveManager::WaveManager() {
    numWave = 0;
}

void WaveManager::update() {
    for(auto it = waves.begin(); it != waves.end(); it++){
        if((*it)->isEmpty){
            waves.erase(it);
            continue;
        }
        (*it)->update();
    }
}

void WaveManager::addWave() {
    switch (numWave) {
        case 0:
            waves.push_back(new Wave(gameLoopCounter, {{basicEnemy, 1, 0},
                                           {basicEnemy, 1, 50},
                                           {basicEnemy, 1, 100},
                                           {basicEnemy, 1, 150},
                                           {basicEnemy, 1, 200},
                                           {basicEnemy, 1, 250}}));
            break;
        case 1:
            waves.push_back(new Wave(gameLoopCounter, {{basicEnemy, 2, 0},
                                           {basicEnemy, 2, 50},
                                           {basicEnemy, 2, 100},
                                           {basicEnemy, 2, 150},
                                           {basicEnemy, 2, 200},
                                           {basicEnemy, 2, 250}}));
            break;
        case 2:
            waves.push_back(new Wave(gameLoopCounter, {{basicEnemy, 3, 0},
                                           {basicEnemy, 3, 50},
                                           {basicEnemy, 3, 100},
                                           {basicEnemy, 3, 150},
                                           {basicEnemy, 3, 200},
                                           {basicEnemy, 3, 250}}));
            break;
        case 3:
            waves.push_back(new Wave(gameLoopCounter, {{basicEnemy,  10, 0},
                                           {basicEnemy,  10, 50},
                                           {basicEnemy,  10, 100},
                                           {basicEnemy,  10, 150},
                                           {flyingEnemy, 1,  150},
                                           {flyingEnemy, 1,  150},
                                           {flyingEnemy, 1,  150},
                                           {basicEnemy,  10, 200},
                                           {basicEnemy,  10, 250}}));
            break;
        default:
            std::cout << "no " << numWave << ". wave implemented" << std::endl;
            waves.push_back(new Wave(gameLoopCounter, {{basicEnemy,  10, 0},
                                                       {basicEnemy,  10, 50},
                                                       {basicEnemy,  10, 100},
                                                       {basicEnemy,  10, 150},
                                                       {flyingEnemy, 1,  150},
                                                       {flyingEnemy, 1,  150},
                                                       {flyingEnemy, 1,  150},
                                                       {basicEnemy,  10, 200},
                                                       {basicEnemy,  10, 250}}));
    }
    numWave++;
}
