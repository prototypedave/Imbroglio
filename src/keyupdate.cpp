#include "Imbroglio/headerFiles/main.hpp"

Vector2d rotate2d(Vector2d vector, double rotSpeed)
{
    Matrix2d rotate;
    rotate << std::cos(rotSpeed), -std::sin(rotSpeed),
    std::sin(rotSpeed), std::cos(rotSpeed);
    return (rotate * vector);
}

void App::updateData(double frameTime) 
{
    double moveSpeed = frameTime * 4;
    double rotSpeed = frameTime * 2;
    if (state->keyHandler.isPressed(SDLK_q) || state->keyHandler.isPressed(SDLK_ESCAPE)) {
        state->done = true;
        return;
    }
    if (state->keyHandler.isPressed(SDLK_LEFT)) 
    {
        state->dir = rotate2d(state->dir, rotSpeed);
        state->viewPlane = rotate2d(state->viewPlane, rotSpeed);
    }
    if (state->keyHandler.isPressed(SDLK_RIGHT)) {
        state->dir = rotate2d(state->dir, -rotSpeed);
        state->viewPlane = rotate2d(state->viewPlane, -rotSpeed);
    }
    if (state->keyHandler.isPressed(SDLK_UP)) {
        double tmp = state->pos(0);
        if (!state->layout->map[int(state->pos(0) + state->dir(0) * moveSpeed)][int(state->pos(1))]) {
            state->pos(0) += state->dir(0) * moveSpeed;
        }
        if (!state->layout->map[int(tmp)][int(state->pos(1) + state->dir(1) * moveSpeed)]) {
            state->pos(1) += state->dir(1) * moveSpeed;
        }
    }
    if (state->keyHandler.isPressed(SDLK_DOWN)) {
        double tmp = state->pos(0);
        if (!state->layout->map[int(state->pos(0) - state->dir(0) * moveSpeed)][int(state->pos(1))])
            state->pos(0) -= state->dir(0) * moveSpeed;
        if (!state->layout->map[int(tmp)][int(state->pos(1) - state->dir(1) * moveSpeed)])
            state->pos(1) -= state->dir(1) * moveSpeed;
    }
    if (state->keyHandler.isPressed(SDLK_a)) {
        double tmp = state->pos(0);
        if (!state->layout->map[int(state->pos(0) - state->dir(1) * moveSpeed)][int(state->pos(1))])
            state->pos(0) -= state->dir(1) * moveSpeed;
        if (!state->layout->map[int(tmp)][int(state->pos(1) + state->dir(0) * moveSpeed)])
            state->pos(1) += state->dir(0) * moveSpeed;
    }
    if (state->keyHandler.isPressed(SDLK_d)) {
        double tmp = state->pos(0);
        if (!state->layout->map[int(state->pos(0) + state->dir(1) * moveSpeed)][int(state->pos(1))])
            state->pos(0) += state->dir(1) * moveSpeed;
        if (!state->layout->map[int(tmp)][int(state->pos(1) - state->dir(0) * moveSpeed)])
            state->pos(1) -= state->dir(0) * moveSpeed;

    }
    if (state->keyHandler.isPressed(SDLK_p) && Mix_PlayingMusic())
        Mix_PauseMusic();
    else if (state->keyHandler.isReleased(SDLK_p) && Mix_PausedMusic())
        Mix_ResumeMusic();
    state->showFPS = state->keyHandler.isPressed(SDLK_f);
    state->showMap = state->keyHandler.isPressed(SDLK_m);
}
