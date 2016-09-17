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

void spawnEnemy(vector <Enemy> &enemies){
    enemies.push_back(Enemy(, 100, 10));
}

void updateEnemies(vector <Enemy> &enemies){
    for (int i = 0; i < enemies.size(); i++){
        enemies[i].update();
    }
}

void gameLoop(SDL_Renderer *renderer, vector <Enemy> &enemies) {
    /*
    Sprite testSprite = Sprite(0, 0, WINDOW_WIDTH / 11, WINDOW_HEIGHT / 11,
                               string(CMAKE_SOURCE_DIR) + "/assets/TowerBase.png", renderer);
    Sprite testSprite2 = Sprite(0, 0, WINDOW_WIDTH / 11, WINDOW_HEIGHT / 11,
                                string(CMAKE_SOURCE_DIR) + "/assets/TowerTurret.png", renderer);
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 11; j++) {
            testSprite.draw();
            testSprite.pos.x += testSprite.width;

            testSprite2.draw();
            testSprite2.pos.x += testSprite2.width;
            testSprite2.rotation += 360 / 100;
        }
        testSprite.pos.x = 0;
        testSprite.pos.y += testSprite.height;

        testSprite2.pos.x = 0;
        testSprite2.pos.y += testSprite2.height;
    }
    */
    bool isRunning = true;
    SDL_Event ev;
    Point mousePos;
    mousePos.x = 0;
    mousePos.y = 0;

    time_t t0;
    time_t t1;
    while (isRunning) {
        time(&t0);

        /*
        testSprite.pos.x = 0;
        testSprite.pos.y = 0;
        testSprite2.pos.x = 0;
        testSprite2.pos.y = 0;
        testSprite2.rotation += 1;
        for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 11; j++) {
                testSprite.draw();
                testSprite.pos.x += testSprite.width;

                testSprite2.draw();
                testSprite2.pos.x += testSprite2.width;
            }
            testSprite.pos.x = 0;
            testSprite.pos.y += testSprite.height;

            testSprite2.pos.x = 0;
            testSprite2.pos.y += testSprite2.height;
        }
         */

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

        updateEnemies(enemies);

        time(&t1);
        if (t1 - t0 < 1000000 / FRAMES_PER_SECOND) {
            usleep(1000000 / FRAMES_PER_SECOND - (t1 - t0));
        }
    }
}

int main(int argc, char *argv[]) {
    Map map("/assets/map1.tmx");
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    if (initWindowAndRenderer(&window, &renderer) != 0) {
        return 1;
    }
    SDL_RenderPresent(renderer);

    vector<Enemy> enemies;
    spawnEnemy(enemies);

    gameLoop(renderer, enemies);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}