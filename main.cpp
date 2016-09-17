#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <unistd.h>
#include <time.h>

#include "GameObject.h"
#include "Enemy.h"
#include "Map.h"
#include "config.h"
#include "colors.h"
#include "TextOutput.h"
#include "tmxparser/Tmx.h"

static Map map("/assets/map1.tmx");
static std::vector<GameObject*> allGameObjects; // YOLO

int initWindowAndRenderer(SDL_Window **window, SDL_Renderer **renderer) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    *window = SDL_CreateWindow("PowerDefense", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    if (*window == NULL) {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        return 1;
    } else {
        *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
        if (*renderer == NULL) {
            std::cout << "Could not create renderer: " << SDL_GetError() << std::endl;
            return 2;
        }
    }
    return 0;
}

void spawnEnemy(std::vector<Enemy> &enemies, Map &map, SDL_Renderer *renderer) {
    allGameObjects.push_back(new Enemy(map, 100, 10.0, renderer));
}

void gameLoop(SDL_Renderer *renderer, std::vector<Enemy> &enemies) {
    bool isRunning = true;
    SDL_Event ev;
    Point mousePos;
    mousePos.x = 0;
    mousePos.y = 0;

    time_t t0;
    time_t t1;
    while (isRunning) {
        time(&t0);

        //handling events
        while (SDL_PollEvent(&ev) != 0) {
            switch (ev.type) {
                case SDL_QUIT:
                    isRunning = false;
                    break;
                case SDL_MOUSEMOTION:
                    mousePos.x = ev.motion.x;
                    mousePos.y = ev.motion.y;
            }
        }

        for (GameObject* object : allGameObjects){
            object->update();
            for (Sprite sprite : object->sprites){
                sprite.draw();
            }
        }
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        time(&t1);
        if (t1 - t0 < 1000000 / FRAMES_PER_SECOND) {
            usleep(1000000 / FRAMES_PER_SECOND - (t1 - t0));
        }
    }
}

int main(int argc, char *argv[]) {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    if (initWindowAndRenderer(&window, &renderer) != 0) {
        return 1;
    }
    SDL_RenderPresent(renderer);

    std::vector<Enemy> enemies;
    spawnEnemy(enemies, map, renderer);

    gameLoop(renderer, enemies);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
