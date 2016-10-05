#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <unistd.h>
#include <time.h>


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
#include "mouseManager.h"
#include "GUIObject.h"
#include "Button.h"

//std::vector<SDL_Texture *> Tower::textures;

Map map;
std::vector<GameObject *> allGameObjects; // YOLO
std::vector<GUIObject *> allGUIObjects;
SDL_Renderer *renderer;

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

void spawnEnemy(std::vector<Enemy> &enemies, Map &map, SDL_Renderer *renderer) {
	allGameObjects.push_back(new Enemy(map, 100, 1.0));
}

void gameLoop(std::vector<Enemy> &enemies) {
	bool isRunning = true;
	SDL_Event ev;
	Point mousePos = {0, 0};

	time_t t0;
	time_t t1;

	int temp = 0;
	while (isRunning) {
		time(&t0);

		//spawn enemies
		if (temp % 30 == 0) {
			spawnEnemy(enemies, map, renderer);
		}
		if (temp == 0) {
			//spawnEnemy(enemies, map, renderer);
		}
		temp++;

		map.draw();
		//drawStats();
		for (GameObject *object : allGameObjects) {
			object->update();
			for (Sprite sprite : object->sprites) {
				sprite.draw();
			}
		}

		for (GUIObject* object: allGUIObjects){
			object->draw();
		}
		//TextOutput::getInstance()->drawTextAndRect("TEst", 600, 100, 100, 30, 8, 0, COLOR_RED, COLOR_GREEN);

		//handling events
		while (SDL_PollEvent(&ev) != 0) {
			switch (ev.type) {
				case SDL_QUIT:
					isRunning = false;
					break;
				case SDL_MOUSEMOTION:
					mousePos.x = ev.motion.x;
					mousePos.y = ev.motion.y;
				case SDL_MOUSEBUTTONDOWN:
					break;
			}
		}
		mouseHandler(mousePos, ev);

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
	if (initWindowAndRenderer(&window) != 0) {
		return 1;
	}

	std::vector<Enemy> enemies;
	allGameObjects.push_back(new Tower(10, 6));
	allGameObjects.push_back(new Tower(4, 3));
	allGameObjects.push_back(new Tower(13, 9));

	initTowerMenu();

	map = Map("/assets/map1.tmx");

	gameLoop(enemies);

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
