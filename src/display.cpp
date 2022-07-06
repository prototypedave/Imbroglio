#include "main.hpp"

void App::displayFPS(double fps) 
{
    int w, h;
    SDL_QueryTexture(state->fpsTex, NULL, NULL, &w, &h);
    auto fpsString = std::to_string(fps);
    SDL_Rect destR = {0, 0, w, h};
    SDL_RenderCopy(state->renderer, state->fpsTex, NULL, &destR);
    for (char c : fpsString) 
    {
        try {
            SDL_Texture *tex = state->fontCache.at(c);
            destR.x += w;
            SDL_QueryTexture(tex, NULL, NULL, &w, &h);
            destR.w = w;
            SDL_RenderCopy(state->renderer, tex, NULL, &destR);
	} catch (std::out_of_range) 
	{
	    continue;
	}
    }
}
