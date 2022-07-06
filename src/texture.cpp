#include "main.hpp"

#define width 1080
#define height 640

void App::drawTexture(int x, int side, int lineheight, double perpWallDist, int drawstart, int drawend, Vector2d& ray, Vector2i &mapPos) 
{
    //calculate value of wallX
    double wallX; //where exactly the wall was hit
    if (side == 1) 
        wallX = state->pos(0) + perpWallDist * ray(0);
    else 
        wallX = state->pos(1) + perpWallDist * ray(1);
    wallX -= floor(wallX);

    //x coordinate on the texture
    int texX = floor(wallX * 256);
    if(side == 0 && ray(0) > 0) 
        texX = 256 - texX - 1;
    if(side == 1 && ray(1) < 0) 
        texX = 256 - texX - 1;

    for(int y = drawstart; y < drawend; y++)
    {
        int d = (y + (lineheight - height) / 2) * 256;
        int texY = ((d * 256) / lineheight) / 256;
        uint32_t color = ((uint32_t *)(textures[state->layout->map[mapPos(0)][mapPos(1)]])->pixels)[texY * 256 + texX];

	//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
        if(side == 1) 
            color = ((color >> 1) & 0x007f7f7f) + 0xff000000;
        SDL_LockSurface(buffer);
        ((uint32_t *)buffer->pixels)[y * buffer->w + x] = color;
        SDL_UnlockSurface(buffer);
    }

}

