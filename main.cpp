#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <unistd.h>
#include <memory>
#include <chrono>
#include <sys/time.h>

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

Map map;
std::vector<std::unique_ptr<GameObject> > allGameObjects;
GUIObject *root = new GUIObject();
SDL_Renderer *renderer;
int lives = 5;
Gamestats gamestats = {0, 1000};
bool gameIsRunning = false;

//YOLO = YOLO_MAX;
DisplayPoint mousePos   = {0, 0};
DisplayPoint clickedPos = {0, 0};
bool isCLicked = false;
bool mouseRelease = false;

TextOutput *TextOutput::instance = NULL;

int initWindowAndRenderer(SDL_Window **window) {
    SDL_Init(SDL_INIT_VIDEO);
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
    bool isRunning = true;
    SDL_Event ev;
    Point mousePos = {0, 0};

    timeval tv;
    int enemyCount = 0;
    int levelCount = 1;
    while (isRunning) {
        gettimeofday(&tv, NULL);
        double t0 = (double) (tv.tv_sec) + 0.000001 * tv.tv_usec;
        double t1 = t0;

        //spawn enemies
        if (gameIsRunning && enemyCount % 50 == 0) {
            if(enemyCount % 300 == 0){
                levelCount++;
            }
            //allGameObjects.push_back(new Enemy(map, 100, 1.0));
            allGameObjects.push_back(std::make_unique<BasicEnemy>(map, levelCount));
        }
        enemyCount++;

        map.draw();
        //drawStats();
        for (int i = 0; i < allGameObjects.size(); i++) {
            auto object = allGameObjects[i].get();
            object->update();
            for (auto sprite : object->sprites) {
                sprite.draw();
            }
        }
        //clean up dead oobjects
        for (auto it = allGameObjects.begin(); it != allGameObjects.end();) {
            if ((*it)->dead) {
                it = allGameObjects.erase(it);
            } else {
                it++;
            }
        }

        for(auto element: root->traverse()){
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

        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);

        gettimeofday(&tv, NULL);
        t1 = (double) (tv.tv_sec) + 0.000001 * tv.tv_usec;
        if (t1 - t0 < 1000000.0 / FRAMES_PER_SECOND) {
            usleep((__useconds_t)(1000000.0 / FRAMES_PER_SECOND - (t1 - t0)));
        }
    }
}

int main(int argc, char *argv[]) {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    if (initWindowAndRenderer(&window) != 0) {
        return 1;
    }

    GUI::initGUI();
    map = Map("/assets/map1.tmx");

    gameLoop();

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
