#pragma once

struct GridPoint;
struct DisplayPoint;

struct Point{
    float x;
    float y;

    // move this Point length units towards the other Point
    void moveTowards(const Point other, float length);
    GridPoint snap() const;
    DisplayPoint displayPoint() const;
};

struct DisplayPoint{
    int x;
    int y;

    GridPoint snap() const;
    Point point() const;
};

struct GridPoint{
    int x;
    int y;

    Point center() const;
};
