#include "Point.h"
#include "util.h"
#include "config.h"

#include <math.h>

void Point::moveTowards(const Point other, float length){
    float dist = distance(*this, other);
    if(dist < length){
        this->x = other.x;
        this->y = other.y;
    } else {
        this->x += (other.x - this->x) * length/dist;
        this->y += (other.y - this->y) * length/dist;
    }
}

GridPoint Point::snap() const{
    return { (int)this->x / TILE_WIDTH, (int)this->y / TILE_HEIGHT };
}

GridPoint DisplayPoint::snap() const{
    return { this->x / TILE_WIDTH, this->y / TILE_HEIGHT };
}

DisplayPoint Point::displayPoint() const{
    return { (int)this->x , (int)this->y };
}

Point DisplayPoint::point() const{
    return { (float) this->x, (float) this->y };
}

Point GridPoint::center() const{
    return { (this->x + 0.5f) * TILE_WIDTH, (this->y + 0.5f) * TILE_WIDTH };
}
