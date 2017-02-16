#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <unistd.h>
#include <memory>
#include <chrono>
#include <sys/time.h>
#include <cstdlib>
#include <stdlib.h>

#include "Point.h"
#include "Tower.h"
#include "Sprite.h"
#include "Shot.h"
#include "GameObject.h"
#include "Enemy.h"
#include "BasicEnemy.h"
#include "Map.h"
#include "TextOutput.h"
#include "GUI.h"
#include "eventHandler.h"
#include "GUIObject.h"
#include "gamestats.h"
#include "config.h"
#include "WaveManager.h"
#include "EnemyType.h"
#include "Lightning.h"
#include "TeslaGround.h"
#include "TeslaCoil.h"

Map map;
std::vector<std::unique_ptr<GameObject> > allGameObjects;
GUIObject *root = new GUIObject(defaultValue);
SDL_Renderer *renderer;
SDL_Texture *destTextureMap;
SDL_Texture *destTextureGUI;
Gamestats gamestats = {0, START_MONEY,0,TIME_TO_PREPARE, START_LIVES};
bool gameIsRunning = false; //game is not paused
uint32_t gameLoopCounter = 0;

//YOLO = YOLO_MAX;
DisplayPoint mousePos = {0, 0};
DisplayPoint clickedPos = {0, 0};
bool isCLicked = false;
bool mouseRelease = false;
WaveManager waveManager = WaveManager();


int initWindowAndRenderer(SDL_Window **window) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Init(SDL_INIT_AUDIO);
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 1, 4096);
    TTF_Init();
    *window = SDL_CreateWindow("PowerDefense", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    if (*window == NULL) {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        return 1;
    } else {
        renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == NULL) {
            std::cout << "Could not create renderer: " << SDL_GetError() << std::endl;
            return 2;
        }
    }

    return 0;
}

void gameLoop() {
    bool isRunning = true; //game is running

    //variables for event manager
    SDL_Event ev;
    Point mousePos = {0, 0};

    //variables for real time issues
    timeval tv;

    //destination rect for map rendering
    SDL_Rect destRect;
    destRect.x = 0;
    destRect.y = 0;
    destRect.w = MAP_WIDTH * TILE_WIDTH;
    destRect.h = MAP_HEIGHT * TILE_HEIGHT;

    //textures for renderTarget
    destTextureMap = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
                                       MAP_WIDTH * TILE_WIDTH,
                                       MAP_HEIGHT * TILE_HEIGHT); //TODO: don't know which pixelformat
    destTextureGUI = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WINDOW_WIDTH,
                                       WINDOW_HEIGHT); //TODO: don't know which pixelformat

    Mix_PlayMusic(Cache::getMusic("/audio/beat1.wav"), -1);

    while (isRunning) {
        //update time variables
        gettimeofday(&tv, NULL);
        double t0 = (double) (tv.tv_sec) + 0.000001 * tv.tv_usec;
        double t1 = t0;


        //clear renderTargets
        SDL_SetRenderTarget(renderer, destTextureMap);
        SDL_RenderClear(renderer);
        SDL_SetRenderTarget(renderer, destTextureGUI);
        SDL_RenderClear(renderer);

        //waveHandling
        waveManager.update();

        //update and draw GameObjects
        map.draw();
        for (int i = 0; i < allGameObjects.size(); i++) {
            auto object = allGameObjects[i].get();
            if (gameIsRunning) {
                object->update();
            }
            for (auto sprite : object->sprites) {
                sprite.draw();
            }
            object->draw();
        }

        //clean up dead objects
        for (auto it = allGameObjects.begin(); it != allGameObjects.end();) {
            if ((*it)->dead) {
                it = allGameObjects.erase(it);
            } else {
                it++;
            }
        }

        //draw GUI
        for (auto element: root->traverse()) {
            element->draw();
        }
        //handling events
        while (SDL_PollEvent(&ev) != 0) {
            if (ev.type == SDL_QUIT) {
                isRunning = false;
                break;
            } else {
                eventHandler::handleEvent(ev);
            }
        }

        //render everything on screen
        SDL_SetRenderTarget(renderer, NULL);
        SDL_RenderCopy(renderer, destTextureGUI, NULL, NULL);
        SDL_RenderCopy(renderer, destTextureMap, NULL, &destRect);
        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

        //handling real time issues for constant frame rate
        gettimeofday(&tv, NULL);

        if (gameIsRunning) {
            gameLoopCounter++;
        }
        t1 = (double) (tv.tv_sec) + 0.000001 * tv.tv_usec;
        if (t1 - t0 < 1000000.0 / FRAMES_PER_SECOND) {
            usleep((__useconds_t) (1000000.0 / FRAMES_PER_SECOND - (t1 - t0)));
        }
    }
}

int main(int argc, char *argv[]) {
    SDL_Window *window = nullptr;
    renderer = nullptr;
    if (initWindowAndRenderer(&window) != 0) {
        return 1;
    }
    srand48(1337);
    GUI::initGUI();
    map = Map("/assets/map2.tmx");
    allGameObjects.push_back(std::make_unique<TeslaGround>(GridPoint(10,2)));
    allGameObjects.push_back(std::make_unique<TeslaGround>(GridPoint(5,4)));
    allGameObjects.push_back(std::make_unique<TeslaGround>(GridPoint(2,2)));
    allGameObjects.push_back(std::make_unique<TeslaCoil>(GridPoint(3,3)));
    gameLoop();
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
