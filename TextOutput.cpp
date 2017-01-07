#include "TextOutput.h"
#include "config.h"

void TextOutput::drawText(const std::string text, GridPoint pos, const int size, FontType fontType) {
    SDL_SetRenderTarget(renderer, destTextureGUI);
    SDL_Rect destRect;
    destRect.x = pos.upperLeft().x;
    destRect.y = pos.upperLeft().y;
    destRect.w = (int)text.length() * size;
    destRect.h = 3 * size;
    SDL_RenderCopy(renderer, Cache::getText(text, fontType), NULL, &destRect);
}

void TextOutput::drawTextAndRect(const std::string text, GridPoint pos, const int w, const int h, const int size,
                     const FontType fontType, const SDL_Color backgroundColor) {
    SDL_SetRenderTarget(renderer, destTextureGUI);
    SDL_Rect rectBorder;
    rectBorder.x = pos.upperLeft().x;
    rectBorder.y = pos.upperLeft().y;
    rectBorder.w = w * TILE_WIDTH;
    rectBorder.h = h * TILE_HEIGHT;
    SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    SDL_RenderDrawRect(renderer, &rectBorder);
    SDL_SetRenderDrawColor(renderer, COLOR_BLACK.r, COLOR_BLACK.g, COLOR_BLACK.b, COLOR_BLACK.a);
    drawText(text, pos + GridPoint ((int) ((w * TILE_WIDTH - size * text.length()) / 2)/TILE_WIDTH,
                                    (int) ((h * TILE_HEIGHT - size * 3) / 2)/TILE_HEIGHT), size, fontType);
}