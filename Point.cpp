#include "Point.h"
#include "util.h"

void Point::moveTowards(const Point other, float length){
    float dist = distance(*this, other);
    if(dist < length){
        this->x = other.x;
        this->y = other.y;
    } else {
        this->x += (other.x - other.x) * length/dist;
        this->y += (other.y - other.y) * length/dist;
    }
}
