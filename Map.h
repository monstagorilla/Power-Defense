#include "tmxparser/Tmx.h"
#include "Point.h"

class Map {
	private:
        Tmx::Map tmxmap;
    public:
        Map(const std::string& filename);
        std::vector<Point> path;
};
