#include "Imbroglio/headerFiles/main.hpp"

#define width 1080
#define height 640

void App::render3d() 
{
    SDL_SetRenderDrawColor(state->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(state->renderer);
    int w, h;
    SDL_GetWindowSize(state->window, &w, &h);
    SDL_LockSurface(buffer);
    memset(buffer->pixels, 0x00 , buffer->h * buffer->pitch);
    SDL_UnlockSurface(buffer);
    for (int x = 0; x < w; x++) {
        drawLine(x);
    }
    SDL_UpdateTexture(buffTex, nullptr, buffer->pixels, buffer->pitch);
    SDL_RenderCopy(state->renderer, buffTex, nullptr, nullptr);
}

void App::render2d() 
{
    int w, h;
    SDL_GetWindowSize(state->window, &w, &h);
    float vp_scale = (float(w) * 0.25 /state->layout->columns <= float(h)* 0.25 /state->layout->rows) ? float(w)* 0.25 /state->layout->columns : float(h)* 0.25 /state->layout->rows;

    SDL_Rect viewport;
    viewport.h = vp_scale * state->layout->rows;
    viewport.w = vp_scale * state->layout->columns;
    viewport.x = w - viewport.w;
    viewport.y = 0;

    SDL_SetRenderDrawColor(state->renderer, 0x4B, 0x4B, 0x4B, 0x00);
    SDL_RenderSetViewport(state->renderer, NULL);
    SDL_RenderSetScale(state->renderer, 1, 1);
    SDL_RenderFillRect(state->renderer, &viewport);
    SDL_RenderSetViewport(state->renderer, &viewport);
    SDL_RenderSetScale(state->renderer, vp_scale, vp_scale);
    SDL_SetRenderDrawColor(state->renderer, 0x8F, 0x8F, 0x8F, 0x00);
    for (uint32_t i = 0; i < state->layout->rows; i++) {
        for (uint32_t j = 0; j < state->layout->columns; j++) {
            if (state->layout->map[i][j] == 0) {
		SDL_Rect block = {int(j), int(i), 1, 1};
                SDL_RenderFillRect(state->renderer, &block);
	    }
	}
    }	
    SDL_RenderSetScale(state->renderer, vp_scale / 4, vp_scale / 4);
    SDL_SetRenderDrawColor(state->renderer, 0xFF, 0x00, 0x00, 0x00);
    SDL_RenderDrawPoint(state->renderer, int(state->pos(1) * 4), int(state->pos(0) * 4));
    SDL_RenderSetViewport(state->renderer, NULL);
    SDL_RenderSetScale(state->renderer, 1, 1);
}
