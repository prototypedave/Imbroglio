#include "main.hpp"

void App::getEvents() 
{
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch(e.type) {
            case SDL_QUIT:
            state->done = true;
            break;

	    case SDL_KEYDOWN: case SDL_KEYUP:
            state->keyHandler.handleKeyEvent(e.key);
            break;

	    default:
            break;
	}
    }
}
