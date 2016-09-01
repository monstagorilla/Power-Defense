#pragma once

struct Point{
    int x;
    int y;
};

class GameObject{
public:
    GameObject();
    virtual ~GameObject();

    virtual void update() = 0;

    Point pos;
    std::vector<Sprite> sprites;
};
