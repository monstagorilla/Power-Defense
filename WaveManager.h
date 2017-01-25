#pragma once

#include <vector>
class Wave;

class WaveManager {
public:
    WaveManager();
    void update();
    void addWave();
    int nextWaveCountdown;
private:
    uint32_t startLastWave;
    int startFirstWave;
    int numWave;
    std::vector<Wave*> waves;
};