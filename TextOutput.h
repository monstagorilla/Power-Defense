#pragma once

class TextOutput {
public:
    static TextOutput *getInstance(SDL_Renderer *renderer) {
        static MemoryHandler mh;
        if (!instance) {
            instance = new TextOutput(renderer);
        }
        return instance;
    }

    void drawText(const std::string text, const int x, const int y, const int w, const int h, const int font,
                  const SDL_Color color) {
        if (font >= 0 && font < fonts.size()) {
            SDL_Surface *surfaceMessage = TTF_RenderText_Solid(fonts[font], text.c_str(), color);
            SDL_Texture *message = SDL_CreateTextureFromSurface(this->renderer, surfaceMessage);
            SDL_Rect destRect;
            destRect.x = x;
            destRect.y = y;
            destRect.w = w;
            destRect.h = h;
            SDL_RenderCopy(renderer, message, NULL, &destRect);
        } else {
            std::cout << "Illegal FontIndex" << std::endl;
        }
    }

private:
    static TextOutput *instance;
    std::vector<TTF_Font *> fonts;
    SDL_Renderer *renderer;

    TextOutput(SDL_Renderer *renderer) {
        this->renderer = renderer;
        addFont(std::string(CMAKE_SOURCE_DIR) + "/fonts/orangejuice.ttf", 100);
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

    class MemoryHandler {TextOutput *TextOutput::instance = NULL;
    public:
        ~MemoryHandler() {
            if (TextOutput::instance != NULL) {
                delete TextOutput::instance;
                TextOutput::instance = NULL;
            }
        }
    };
};

TextOutput *TextOutput::instance = NULL;