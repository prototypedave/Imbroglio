#include "Imbroglio/headerFiles/main.hpp"

#define width 1080
#define height 640

void App::initialize(std::string filename) 
{
    state->layout = new Layout(filename, std::ref(state->pos));
    state->dir << 0, 1;
    state->viewPlane << 2.0/3, 0;
      
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) 
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
        throw std::runtime_error("SDL_Init failed");
    }
    if (!(state->window = SDL_CreateWindow("Imbroglio", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_RESIZABLE))) 
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window: %s", SDL_GetError());
        throw std::bad_alloc();
    }
    if (!(state->renderer = SDL_CreateRenderer(state->window, -1, SDL_RENDERER_ACCELERATED))) 
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create renderer: %s", SDL_GetError());
        throw std::bad_alloc();
    }
    makeGlyphs("path");
    buffer = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_BGRA32);
    if (!buffer) {
         throw std::bad_alloc();
    }
    buffTex = SDL_CreateTexture(state->renderer, buffer->format->format, SDL_TEXTUREACCESS_STREAMING, width, height);
    if (!buffTex) {
        throw std::bad_alloc();
    }
    SDL_SetTextureBlendMode(buffTex, SDL_BLENDMODE_BLEND);
    if (IMG_Init(IMG_INIT_JPG) != IMG_INIT_JPG)
        throw std::runtime_error("Texture initialization failed");
    textures[1] = IMG_Load("Imbroglio/images/wood.jpg");
    textures[2] = IMG_Load("Imbroglio/images/metal.jpg");
    textures[3] = IMG_Load("Imbroglio/images/curtain.jpg");
    textures[4] = IMG_Load("Imbroglio/images/stone_moss.jpg");
    textures[5] = IMG_Load("Imbroglio/images/bark.jpg");
    textures[6] = IMG_Load("Imbroglio/images/privat_parkering.jpg");
    textures[7] = IMG_Load("Imbroglio/images/grass.jpg");
    textures[8] = IMG_Load("Imbroglio/images/lava.jpg");
								        
    SDL_Surface *skySurf = IMG_Load("Imbroglio/images/sky.jpg");
    if (!skySurf)
        throw std::bad_alloc();
    sky = SDL_CreateTextureFromSurface(state->renderer, skySurf);
    SDL_SetTextureBlendMode(sky, SDL_BLENDMODE_BLEND);
    SDL_FreeSurface(skySurf);
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
        throw std::bad_alloc();
    if (!(music = Mix_LoadMUS("Imbroglio/audio/Game_of_Thrones.wav")))
        throw std::runtime_error("Could not load music");
}
