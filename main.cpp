#include "GameObject.h"
#include "config.h"
#include "SDL.h"

void initGame(){
	std::vector<GameObject> gameObjects;  
}

void gameUpdateLoop(){

}

void createWindow(){
	
}

int main(int argc, char *argv[]) {
	SDL_Window *window;                    // Declare a pointer
	SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

	// Create an application window with the following settings:
    window = SDL_CreateWindow(
        "POWERDEFENSE",                  // window title
        0,           // initial x position
        0,           // initial y position
        WINDOW_WIDTH,                               // width, in pixels
        WINDOW_HEIGHT,                               // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );

    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }
 //gameLoop()

    SDL_Delay(3000);  // Pause execution for 3000 milliseconds, for example

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();




    return 0;
}
