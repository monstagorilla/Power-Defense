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
    DisplayPoint operator+(const DisplayPoint other) {
        return { x+other.x, y+other.y };
    }
    DisplayPoint operator-(const DisplayPoint other) {
        return { x-other.x, y-other.y };
    }
};

struct GridPoint{
    int x;
    int y;

    Point center() const;
    DisplayPoint upperLeft();
    GridPoint operator+(const GridPoint other) {
        return { x+other.x, y+other.y };
    }
    GridPoint operator-(const GridPoint other) {
        return { x-other.x, y-other.y };
    }
    friend bool operator==(const GridPoint a, const GridPoint b) {
        return a.x == b.x && a.y == b.y;
    }
};
