#pragma once

#include "Point.h"
#include "globals.h"
#include "textboxes.h"

static bool isClicked = false;

static void mouseHandler(const Point pos, SDL_Event &ev) {
	int xPos = pos.x / TILE_WIDTH;
	int yPos = pos.y / TILE_HEIGHT;

	//display rect on the focused map tile
	if (xPos <= MAP_WIDTH && !map.isGround(xPos, yPos)) {
		SDL_Rect rect;
		rect.x = xPos * TILE_WIDTH;
		rect.y = yPos * TILE_HEIGHT;
		rect.w = TILE_WIDTH;
		rect.h = TILE_HEIGHT;
		SDL_RenderDrawRect(renderer, &rect);
	}

	//managing mouse clicks
	if (ev.button.state == SDL_PRESSED) {
		isClicked = true;
	} else if (isClicked) {
		isClicked = false;
		if (ev.button.button == SDL_BUTTON_LEFT) {
			if (xPos <= MAP_WIDTH) {
				Tower *actualTower = NULL;
				for (GameObject *object : allGameObjects) {
					if ((int) object->pos.x == xPos && (int) object->pos.y == yPos) {
						actualTower = (Tower *) object;
						break;
					}
				}
				if (actualTower != NULL) {

				}
			} else {

			}
		}

	}
}


static void mouseClick(const Point pos) {
}
