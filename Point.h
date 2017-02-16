#pragma once

class GridPoint;
class DisplayPoint;
class Point;

class Point{
public:
    Point();
    Point(const float x, const float y);
    ~Point();

    float x;
    float y;

    // move this Point length units towards the other Point
    void moveTowards(const Point other, float length);
    GridPoint snap() const;
    DisplayPoint displayPoint() const;
    Point operator+(const Point other);
    Point operator-(const Point other);
    Point operator*(const float scalar) const;
};

class DisplayPoint{
public:
    DisplayPoint();
    DisplayPoint(const int x, const int y);
    ~DisplayPoint();

    int x;
    int y;

    GridPoint snap() const;
    Point point() const;
    DisplayPoint operator+(const DisplayPoint other);
    DisplayPoint operator-(const DisplayPoint other);
};

class GridPoint{
public:
    GridPoint();
    GridPoint(const int x , const int y);
    ~GridPoint();

    int x;
    int y;

    Point center() const;
    DisplayPoint upperLeft();
    GridPoint operator+(const GridPoint other);
    GridPoint operator-(const GridPoint other);
    friend bool operator==(const GridPoint a, const GridPoint b);
};
