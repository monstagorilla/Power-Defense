#include "eventHandler.h"

#include "Point.h"
#include "globals.h"
#include "GUIObject.h"

void eventHandler::handleEvent(SDL_Event &ev) {
    mouseRelease = false;
    switch (ev.type) {
        case SDL_MOUSEMOTION:
            mousePos = {ev.motion.x, ev.motion.y};
            break;
        case SDL_MOUSEBUTTONDOWN:
            isCLicked = true;
            clickedPos = {ev.motion.x, ev.motion.y};
            break;
        case SDL_MOUSEBUTTONUP:
            if (isCLicked) {
                mouseRelease = true;
            }
            isCLicked = false;
            break;
    }
    for (auto element: root->traverse()) {
        element->update();
    }
    for (auto element: root->traverse()) {
        element->draw();
    }
}
