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

GridPoint Point::snap() {
    return { (unsigned)this->x / TILE_WIDTH, (unsigned)this->y / TILE_HEIGHT };
}

Point GridPoint::center(){
    return { (this->x + 0.5f) * TILE_WIDTH, (this->y + 0.5f) * TILE_WIDTH };
}
