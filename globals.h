#pragma once
// allmighty yolo header... BUUUURRRRR!!!
#include "Map.h"
#include "GameObject.h"
#include "GUIObject.h"
#include "SDL2/SDL.h"

extern Map map;
extern std::vector<GameObject *> allGameObjects;
extern SDL_Renderer* renderer;
extern GUIObject *root;
extern int lives;
