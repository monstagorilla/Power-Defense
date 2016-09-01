#include <SDL2/SDL.h>

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
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Rect r;
    r.x = 50;
    r.y = 50;
    r.w = 50;
    r.h = 50;
    
    SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
    SDL_RenderFillRect( renderer, &r );
    
    SDL_RenderPresent(renderer);
    

    SDL_Delay(3000); // Pause execution for 3000 milliseconds, for example

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();

    return 0;
}
