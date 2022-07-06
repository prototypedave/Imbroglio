#include "Imbroglio/headerFiles/main.hpp"

#define width 1080
#define height 640

void App::drawLine(int x) 
{
    int w, h;
    SDL_GetWindowSize(state->window, &w, &h);
    double t = 2.0 * double(x) / double(w) - 1.0;
    Vector2d ray = state->dir + state->viewPlane * t;
    Vector2i mapPos(state->pos(0), state->pos(1));
    Vector2d dDist = ray.cwiseAbs().cwiseInverse();
    bool hit = false;
    int side = 0;
			    
    Vector2i stepDir;
    Vector2d sideDist;
					    
    if (ray(0) < 0) {
        sideDist(0) = (state->pos(0) - double(mapPos(0))) * dDist(0);
        stepDir(0) = -1;
    } else {
        sideDist(0) = (double(mapPos(0)) + 1.0 - state->pos(0)) * dDist(0);
        stepDir(0) = 1;
    }
    if (ray(1) < 0) {
        sideDist(1) = (state->pos(1) - double(mapPos(1))) * dDist(1);
        stepDir(1) = -1;
    } else {
        sideDist(1) = (double(mapPos(1)) + 1.0 - state->pos(1)) * dDist(1);
        stepDir(1) = 1;
    }
    while (!hit) {
        std::ptrdiff_t i;
        sideDist.minCoeff(&i);
        side = int(i);
        sideDist(i) += dDist(i);
        mapPos(i) += stepDir(i);
           
        if (state->layout->map[mapPos(0)][mapPos(1)]) hit = true;
    }
    double perpWallDist;
    if (side == 0)
        perpWallDist = (mapPos(0) + ((1.0 - stepDir(0)) / 2.0) - state->pos(0)) / ray(0);
    else
        perpWallDist = (mapPos(1) + ((1.0 - stepDir(1)) / 2.0) - state->pos(1)) / ray(1);
    int lineHeight = (int)(h / perpWallDist);
    int drawStart = (h - lineHeight) / 2;
    if (drawStart < 0) drawStart = 0;
    int drawEnd = (lineHeight + h) / 2;
    if (drawEnd >= h) drawEnd = h- 1;
    int color = 0x8F;
    if (side == 1)
    color = 0x4D;
    drawTexture(x, side, lineHeight, perpWallDist, drawStart, drawEnd, ray, mapPos);
}
