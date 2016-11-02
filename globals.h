#pragma once
// allmighty yolo header... BUUUURRRRR!!!

#include <memory>
#include <SDL2/SDL.h>
#include <vector>

struct Gamestats;
class GameObject;
class Map;
class GUIObject;
class DisplayPoint;

extern Map map;
extern std::vector< std::unique_ptr< GameObject > > allGameObjects;
extern SDL_Renderer* renderer;
extern GUIObject *root;
extern int lives;
extern Gamestats gamestats;
extern bool gameIsRunning;

extern DisplayPoint mousePos;
extern DisplayPoint clickedPos;
extern bool isCLicked;
extern bool mouseRelease;
