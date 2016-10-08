#pragma once

#include <SDL2/SDL_ttf.h>

#include "globals.h"
#include "colors.h"
#include "Point.h"

class TextOutput {
public:
	static TextOutput *getInstance() {
		static MemoryHandler mh;
		if (!instance) {
			instance = new TextOutput();
		}
		return instance;
	}

	void drawText(const std::string text, DisplayPoint pos, const int size, const int font,
				  const SDL_Color color) {
		if (font >= 0 && font < fonts.size()) {
			SDL_Surface *surfaceMessage = TTF_RenderText_Solid(fonts[font], text.c_str(), color);
			SDL_Texture *message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
			SDL_Rect destRect;
			destRect.x = pos.x;
			destRect.y = pos.y;
			destRect.w = text.length() * size;
			destRect.h = 3 * size;
			SDL_RenderCopy(renderer, message, NULL, &destRect);
		} else {
			std::cout << "Illegal FontIndex" << std::endl;
		}
	}

	void drawTextAndRect(const std::string text, GridPoint pos, const int w, const int h, const int size,
						 const int font, const SDL_Color foregroundColor, const SDL_Color backgroundColor) {
		SDL_Rect rectBorder;
		rectBorder.x = pos.upperLeft().x;
		rectBorder.y = pos.upperLeft().y;
		rectBorder.w = w * TILE_WIDTH;
		rectBorder.h = h * TILE_HEIGHT;
		SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
		SDL_RenderDrawRect(renderer, &rectBorder);
		SDL_SetRenderDrawColor(renderer, COLOR_BLACK.r, COLOR_BLACK.g, COLOR_BLACK.b, COLOR_BLACK.a);
		drawText(text, pos.upperLeft() + DisplayPoint
                { (int)(w*TILE_WIDTH - size*text.length()  )/2,
                  (int)(h*TILE_HEIGHT- size*3)/2},
                 size, font, foregroundColor);
	}

private:
	static TextOutput *instance;
	std::vector<TTF_Font *> fonts;

	TextOutput() {
		addFont(std::string(CMAKE_SOURCE_DIR) + "/fonts/Raleway-Medium.ttf", 100);
	}

	TextOutput(const TextOutput &);

	~TextOutput() {

	}

	void addFont(const std::string path, const int textSize) {
		const char *cpath = path.c_str();
		TTF_Font *font = TTF_OpenFont(cpath, textSize);
		if (font == NULL) {
			std::cout << SDL_GetError();
		} else {
			fonts.push_back(font);
		}
	}

	class MemoryHandler {
	public:
		~MemoryHandler() {
			if (TextOutput::instance != NULL) {
				delete TextOutput::instance;
				TextOutput::instance = NULL;
			}
		}
	};
};
