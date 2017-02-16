#include <SDL2/SDL.h>
#include <initializer_list>
#include <vector>

#include "GameObject.h"

class Point;

class Lightning : public GameObject {
public:
    Lightning(const Point start, const Point end, const float duration);
    virtual void draw();
    virtual void update();
    virtual ~Lightning();

private:
    Point end;
    int duration;
    std::vector<Point> points;
};
