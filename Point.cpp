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
    return { (this->x + TILE_WIDTH/2) / TILE_WIDTH, (this->y + TILE_HEIGHT/2) / TILE_HEIGHT };
}

DisplayPoint Point::displayPoint() const{
    return { (int)this->x , (int)this->y };
}

Point DisplayPoint::point() const{
    return { (float) this->x, (float) this->y };
}

Point GridPoint::center() const{
    return { (float)this->x * TILE_WIDTH, (float)this->y * TILE_HEIGHT };
}

DisplayPoint GridPoint::upperLeft(){
    return { this->x * TILE_WIDTH - TILE_WIDTH/2, this->y * TILE_HEIGHT - TILE_HEIGHT/2};
}

DisplayPoint GridPoint::left(){
    return { this->x * TILE_WIDTH - TILE_WIDTH/2, this->y * TILE_HEIGHT};
}