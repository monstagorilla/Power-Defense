#pragma once

#include <SDL2/SDL_ttf.h>

#include "globals.h"
#include "colors.h"
#include "Point.h"
#include "font.h"
#include "Cache.h"

class TextOutput {
public:
    static void drawText(const std::string text, GridPoint pos, const int size, FontType fontType);
    static void drawTextAndRect(const std::string text, GridPoint pos, const int w, const int h, const int size,
                                const FontType fontType, const SDL_Color backgroundColor);

private:
    TextOutput() {

    }
    TextOutput(const TextOutput &);
    ~TextOutput() {
    }
};