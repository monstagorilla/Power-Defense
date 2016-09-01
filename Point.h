#pragma once

struct Point{
    float x;
    float y;

    // move this Point length units towards the other Point
    void moveTowards(const Point other, float length);
};
