#pragma once

struct GridPoint;

struct Point{
    float x;
    float y;

    // move this Point length units towards the other Point
    void moveTowards(const Point other, float length);
    GridPoint snap();
};

struct GridPoint{
    unsigned x;
    unsigned y;

    Point center();
};
