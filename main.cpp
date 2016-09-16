#include <SDL2/SDL.h>
#include <string>

#include "GameObject.h"
#include "config.h"

void initGame() {
    std::vector<GameObject> gameObjects;
}

void gameUpdateLoop() {

}

void createWindow() {

}

int main(int argc, char *argv[]) {
    SDL_Window *window; // Declare a pointer
    SDL_Init(SDL_INIT_VIDEO); // Initialize SDL2

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
            "POWERDEFENSE", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);

    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    //gameLoop()

    //drawRect
    /*
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Rect r;
    r.x = 50;
    r.y = 50;
    r.w = 50;
    r.h = 50;
    
    SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
    SDL_RenderFillRect( renderer, &r );
    
    SDL_RenderPresent(renderer);
    */

    //Test Sprite
    //string path = "/home/jonas/ClionProjects/Power-Defense/assets/TowerBase.png"; //Attention!! absolute direction
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Sprite testSprite = Sprite(renderer);
    testSprite.pos.x = 0;
    testSprite.pos.y = 0;
    testSprite.width = WINDOW_WIDTH/11;
    testSprite.height = WINDOW_HEIGHT/11;

    //testSprite.loadImage(string(SDL_GetBasePath()) + "TowerBase.png");
    testSprite.loadImage(CMAKE_SOURCE_DIR + "/assets/TowerBase.png");
    cout<<string(SDL_GetBasePath());
    
    Sprite testSprite2 = Sprite(renderer);
    testSprite2.pos.x = 0;
    testSprite2.pos.y = 0;
    testSprite2.width = WINDOW_WIDTH/11;
    testSprite2.height = WINDOW_HEIGHT/11;
    testSprite2.loadImage(CMAKE_SOURCE_DIR + "/assets/TowerTurret.xcf");

    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 11; j++) {
            testSprite.draw();
            testSprite.pos.x += testSprite.width;

            testSprite2.draw();
            testSprite2.pos.x += testSprite2.width;
            testSprite2.rotation += 360/100;
        }
        testSprite.pos.x = 0;
        testSprite.pos.y += testSprite.height;

        testSprite2.pos.x = 0;
        testSprite2.pos.y += testSprite2.height;
    }

    SDL_RenderPresent(renderer);


    SDL_Delay(30000); // Pause execution for 3000 milliseconds, for example

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();

    return 0;
}