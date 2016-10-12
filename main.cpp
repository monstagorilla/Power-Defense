#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <unistd.h>
#include <time.h>
#include <memory>
#include <chrono>
#include <sys/time.h>


#include "GameObject.h"
#include "Enemy.h"
#include "Map.h"
#include "Tower.h"
#include "config.h"
#include "colors.h"
#include "TextOutput.h"
#include "tmxparser/Tmx.h"
#include "util.h"
#include "textboxes.h"
#include "Shot.h"
#include "eventHandler.h"
#include "GUIObject.h"
#include "Button.h"
#include "BasicTower.h"
#include "GUIFunctions.h"

//std::vector<SDL_Texture *> Tower::textures;

Map map;
std::vector< std::unique_ptr< GameObject > > allGameObjects;
//std::vector<GameObject *> allGameObjects; // YOLO
GUIObject *root = new GUIObject();
SDL_Renderer *renderer;
int lives = 5;

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
    int temp = 0;
    while (isRunning) {
    gettimeofday (&tv, NULL);
    double t0 = (double) (tv.tv_sec) + 0.000001 * tv.tv_usec;
    double t1 = t0;

        //spawn enemies
        if (temp % 50 == 0) {
            //allGameObjects.push_back(new Enemy(map, 100, 1.0));
	    allGameObjects.push_back(std::make_unique<Enemy>(map, 100, 3.0));
        }
        temp++;

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

        for (auto child : root->children) {
            child->draw();
        }

        //handling events
        while (SDL_PollEvent(&ev) != 0) {
            if(ev.type == SDL_QUIT){
                isRunning = false;
                break;
            } else {
                handleEvent(ev);
            }
        }
        
        //TextOutput::getInstance()->drawTextAndRect("test",MAP_WIDTH * TILE_WIDTH, 10,  100, 30, 10, 0, COLOR_GREEN, COLOR_RED);
        //TextOutput::getInstance()->drawText("test", MAP_WIDTH * TILE_WIDTH,100, 8, 0, COLOR_GREEN);

        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);

        gettimeofday (&tv, NULL);
	t1 = (double) (tv.tv_sec) + 0.000001 * tv.tv_usec;
        if (t1 - t0 < 1000000.0 / FRAMES_PER_SECOND) {
            usleep(1000000.0 / FRAMES_PER_SECOND - (t1 - t0));
        }
    }
}

int main(int argc, char *argv[]) {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    if (initWindowAndRenderer(&window) != 0) {
        return 1;
    }
    
    initTowerMenu();
	

    map = Map("/assets/map1.tmx");
    
    addBasicTower({3, 5});
    addBasicTower({8, 7});
    addBasicTower({11, 9});
    

    gameLoop();

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
