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
class WaveManager;

extern Map map;
extern std::vector< std::unique_ptr< GameObject > > allGameObjects;
extern SDL_Renderer* renderer;
extern SDL_Texture* destTextureMap;
extern SDL_Texture* destTextureGUI;
extern GUIObject *root;
extern Gamestats gamestats;
extern bool gameIsRunning;
extern uint32_t gameLoopCounter;
extern WaveManager waveManager;

extern DisplayPoint mousePos;
extern DisplayPoint clickedPos;
extern bool isCLicked;
extern bool mouseRelease;
