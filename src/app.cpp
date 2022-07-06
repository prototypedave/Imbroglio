#include "Imbroglio/headerFiles/main.hpp"

#define width 1080
#define height 640

App::App() 
{
    state = State::getInstance();
}

App::~App() 
{
    delete state;
    if (buffer)
        SDL_FreeSurface(buffer);
    if (buffTex)
        SDL_DestroyTexture(buffTex);
    std::for_each(textures.begin(), textures.end(), [] (SDL_Surface *s) { if (s) SDL_FreeSurface(s);});
    if (sky)
        SDL_DestroyTexture(sky);
    if (music)
        Mix_FreeMusic(music);
    Mix_Quit();
    SDL_Quit();
    TTF_Quit();
    IMG_Quit();
}

bool App::run(std::string filename) 
{
    initialize(filename);
    clock_t newTime, oldTime;
    double movingAverage = 0.015;
    oldTime = clock();
    Mix_FadeInMusic(music, -1, 3000);
    while(!state->done)
    {
        if (sky) 
	{
	    SDL_RenderCopy(state->renderer, sky, nullptr, nullptr);
	}
	render3d();
	if (state->showMap)
	    render2d();
	newTime = clock();
	double frameTime = ((double(newTime - oldTime)) / CLOCKS_PER_SEC);
	oldTime = newTime;
	movingAverage = (movingAverage * 19.0 / 20.0) + (frameTime / 20.0);
	if (state->showFPS)
	    displayFPS(1/movingAverage);
	SDL_RenderPresent(state->renderer);
	getEvents();
	updateData(movingAverage);
    }
    return (true);
}
