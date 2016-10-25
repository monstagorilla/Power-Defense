#pragma once
// allmighty yolo header... BUUUURRRRR!!!

#include <memory>
#include <SDL2/SDL.h>

#include "Map.h"
#include "GameObject.h"
#include "GUIObject.h"
#include "gamestats.h"


class Map;

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
