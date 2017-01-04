#pragma once

#include <vector>
class Wave;

class WaveManager {
public:
    WaveManager();
    void update();
    void addWave();
private:
    int numWave;
    std::vector<Wave*> waves;
};