#pragma once

#include <cstdint>
#include "EnemyType.h"

struct WaveItem{
    EnemyType type;
    unsigned level;
    uint32_t startTime;
};