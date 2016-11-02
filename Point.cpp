#include "Point.h"
#include "util.h"
#include "config.h"

#include <math.h>

void Point::moveTowards(const Point other, float length) {
    float dist = distance(*this, other);
    if (dist < length) {
        this->x = other.x;
        this->y = other.y;
    } else {
        this->x += (other.x - this->x) * length / dist;
        this->y += (other.y - this->y) * length / dist;
    }
}

GridPoint Point::snap() const {
    return {(int) this->x / TILE_WIDTH, (int) this->y / TILE_HEIGHT};
}

GridPoint DisplayPoint::snap() const {
    return {this->x / TILE_WIDTH, this->y / TILE_HEIGHT};
}

DisplayPoint DisplayPoint::operator+(const DisplayPoint other) {
    return {x + other.x, y + other.y};
}

DisplayPoint DisplayPoint::operator-(const DisplayPoint other) {
    return {x - other.x, y - other.y};
}

Point::Point(const float x, const float y) {
    this->x = x;
    this->y = y;
}

DisplayPoint Point::displayPoint() const {
    return {(int) this->x, (int) this->y};
}

Point::~Point() {

}

Point::Point() {
    x = 0;
    y = 0;
}

DisplayPoint::DisplayPoint() {
    x = 0;
    y = 0;
}
GridPoint::GridPoint() {
    x = 0;
    y = 0;
}
Point DisplayPoint::point() const {
    return {(float) this->x, (float) this->y};
}

DisplayPoint::DisplayPoint(const int x, const int y) {
    this->x = x;
    this->y = y;
}

DisplayPoint::~DisplayPoint() {

}

Point GridPoint::center() const {
    return {((float) this->x + 0.5f) * TILE_WIDTH, ((float) this->y + 0.5f) * TILE_HEIGHT};
}

GridPoint GridPoint::operator+(const GridPoint other) {
    return {x + other.x, y + other.y};
}

GridPoint GridPoint::operator-(const GridPoint other) {
    return {x - other.x, y - other.y};
}

bool operator==(const GridPoint a, const GridPoint b) {
    return a.x == b.x && a.y == b.y;
}

DisplayPoint GridPoint::upperLeft() {
    return {this->x * TILE_WIDTH, this->y * TILE_HEIGHT};
}

GridPoint::GridPoint(const int x, const int y) {
    this->x = x;
    this->y = y;
}

GridPoint::~GridPoint() {

}
