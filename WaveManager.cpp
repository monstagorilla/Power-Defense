#include <iostream>
#include "WaveManager.h"
#include "EnemyType.h"
#include "Wave.h"
#include "globals.h"
#include "config.h"

WaveManager::WaveManager() {
    numWave = 0;
    startLastWave = 0;
    startFirstWave = 60;
    nextWaveCountdown = startFirstWave;
}

void WaveManager::update() {
    if (gameIsRunning) {
        if (nextWaveCountdown <= 0) {
            addWave();
        }
        if (!waves.empty()) {
            for (auto it = waves.begin(); it != waves.end(); it++) {
                if ((*it)->isEmpty) {
                    waves.erase(it);
                    continue;
                }
                (*it)->update();
            }
            nextWaveCountdown = (startLastWave - gameLoopCounter + waves.back()->length) / FRAMES_PER_SECOND;
        } else {
            nextWaveCountdown = startFirstWave - gameLoopCounter / FRAMES_PER_SECOND;
        }
    }
}

void WaveManager::addWave() {
    switch (numWave) {
        case 0:
            waves.push_back(new Wave(gameLoopCounter, {{basicEnemy, 1, 0},
                                                       {basicEnemy, 1, 2},
                                                       {basicEnemy, 1, 4},
                                                       {basicEnemy, 1, 6},
                                                       {basicEnemy, 1, 8},
                                                       {basicEnemy, 1, 10}}));
            break;
        case 1:
            waves.push_back(new Wave(gameLoopCounter, {{basicEnemy, 2, 0},
                                                       {basicEnemy, 2, 2},
                                                       {basicEnemy, 2, 4},
                                                       {basicEnemy, 2, 8},
                                                       {basicEnemy, 2, 10},
                                                       {basicEnemy, 2, 12}}));
            break;
        case 2:
            waves.push_back(new Wave(gameLoopCounter, {{basicEnemy, 3, 0},
                                                       {basicEnemy, 3, 2},
                                                       {basicEnemy, 3, 4},
                                                       {basicEnemy, 3, 6},
                                                       {basicEnemy, 3, 8},
                                                       {basicEnemy, 3, 10}}));
            break;
        case 3:
            waves.push_back(new Wave(gameLoopCounter, {{basicEnemy,  10, 0},
                                                       {basicEnemy,  10, 2},
                                                       {basicEnemy,  10, 4},
                                                       {basicEnemy,  10, 6},
                                                       {flyingEnemy, 1,  8},
                                                       {flyingEnemy, 1,  10},
                                                       {flyingEnemy, 1,  12},
                                                       {basicEnemy,  10, 14},
                                                       {basicEnemy,  10, 16}}));
            break;
        default:
            std::cout << "no " << numWave << ". wave implemented" << std::endl;
            waves.push_back(new Wave(gameLoopCounter, {{basicEnemy,  10, 0},
                                                       {basicEnemy,  10, 2},
                                                       {basicEnemy,  10, 4},
                                                       {basicEnemy,  10, 6},
                                                       {flyingEnemy, 1,  8},
                                                       {flyingEnemy, 1,  10},
                                                       {flyingEnemy, 1,  12},
                                                       {basicEnemy,  10, 14},
                                                       {basicEnemy,  10, 16}}));
    }
    numWave++;
    startLastWave = gameLoopCounter;
}
