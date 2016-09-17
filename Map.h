#include "tmxparser/Tmx.h"
#include "Point.h"

enum tiletype {
    Ground = 0,
    Wall   = 1,
};

class Map {
	private:
        Tmx::Map tmxmap;
        std::vector<std::vector<tiletype>> terrain;
    public:
        Map(const std::string& filename);
        std::vector<Point> path;
        int getHeight(){ return tmxmap.GetHeight(); };
        int getWidth (){ return tmxmap.GetWidth();  };
        bool isGround(int x, int y);
};
