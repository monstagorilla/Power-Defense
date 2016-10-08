#pragma once

struct GridPoint;
struct DisplayPoint;

struct Point{
    float x;
    float y;

    // move this Point length units towards the other Point
    void moveTowards(const Point other, float length);
    GridPoint snap();
    DisplayPoint displayPoint();
};

struct DisplayPoint{
    int x;
    int y;

    GridPoint snap();
    Point point();
};

struct GridPoint{
    int x;
    int y;

    Point center();
};
