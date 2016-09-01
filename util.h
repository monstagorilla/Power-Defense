#pragma once

#include <math.h>

#include "Point.h"

static float distance(const Point a, const Point b){
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}
