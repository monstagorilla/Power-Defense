#pragma once

#include <vector>
#include <cstdint>

#include "WaveItem.h"
class Wave {
public:
    Wave(const uint32_t startTime,std::vector<WaveItem> items);
    ~Wave();

    virtual void update();
    bool isEmpty;
    std::vector<WaveItem> items;

private:
    uint32_t startTime;
};