#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <unistd.h>
#include <time.h>

#include "GameObject.h"
#include "Map.h"
#include "config.h"
#include "colors.h"
#include "TextOutput.h"
#include "tmxparser/Tmx.h"

static Map lemap("/assets/map1.tmx");

int initWindowAndRenderer(SDL_Window **window, SDL_Renderer **renderer) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    *window = SDL_CreateWindow("PowerDefense", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    if (*window == NULL) {
        cout << "Could not create window: " << SDL_GetError() << endl;
        return 1;
    } else {
        *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
        if (*renderer == NULL) {
            cout << "Could not create renderer: " << SDL_GetError() << endl;
            return 2;
        }
    }
    return 0;
}

void gameLoop(SDL_Renderer *renderer) {
    Sprite testSprite = Sprite(0, 0, WINDOW_WIDTH / 22, WINDOW_HEIGHT / 22,
                               string(CMAKE_SOURCE_DIR) + "/assets/TowerBase.png", renderer);
    Sprite testSprite2 = Sprite(0, 0, WINDOW_WIDTH / 22, WINDOW_HEIGHT / 22,
                                string(CMAKE_SOURCE_DIR) + "/assets/TowerTurret.png", renderer);
    bool isRunning = true;
    SDL_Event ev;
    Point mousePos;
    mousePos.x = 0;
    mousePos.y = 0;

    time_t t0;
    time_t t1;
    while (isRunning) {
        time(&t0);
        testSprite.pos.x = 0;
        testSprite.pos.y = 0;
        testSprite2.pos.x = 0;
        testSprite2.pos.y = 0;
        testSprite2.rotation += 1;
        for (int i = 0; i < 22; i++) {
            for (int j = 0; j < 22; j++) {
                if(lemap.isGround(i, j)){
                    testSprite.draw();
                    testSprite2.draw();
                }
                testSprite.pos.x += testSprite.width;

                testSprite2.pos.x += testSprite2.width;
            }
            testSprite.pos.x = 0;
            testSprite.pos.y += testSprite.height;

            testSprite2.pos.x = 0;
            testSprite2.pos.y += testSprite2.height;
        }
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
        SDL_RenderPresent(renderer);

        time(&t1);
        if (t1 - t0 < 1000000 / FRAMES_PER_SECOND) {
            usleep(1000000 / FRAMES_PER_SECOND - (t1 - t0));
        }
    }
}

int main(int argc, char *argv[]) {
    lemap = Map("/assets/map1.tmx");
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    if (initWindowAndRenderer(&window, &renderer) != 0) {
        return 1;
    }

    SDL_RenderPresent(renderer);

    gameLoop(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}