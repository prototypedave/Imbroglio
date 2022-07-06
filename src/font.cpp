#include "Imbroglio/headerFiles/main.hpp"

void App::makeGlyphs(std::string fontname) 
{
    if (TTF_Init()) 
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize true type font system: %s", TTF_GetError());
        throw std::runtime_error("TTF_Init failed");
    }
    TTF_Font *font = TTF_OpenFont(fontname.c_str(), 24);
    if (!font)
        throw std::runtime_error("TTF_OpenFont failed");
    SDL_Color fg = {0xff,0xff,0xff,0xff};
    SDL_Surface *textSurf = TTF_RenderText_Blended(font, "FPS: ", fg);
    if (!textSurf)
        throw std::bad_alloc();
    SDL_Texture *fpsTex = SDL_CreateTextureFromSurface(state->renderer, textSurf);
    if (!fpsTex)
        throw std::bad_alloc();
    state->fpsTex = fpsTex;
    SDL_FreeSurface(textSurf);
    for (char c : std::string(".0123456789")) 
    {
        SDL_Surface *glyphSurf = TTF_RenderGlyph_Blended(font, c, fg);
        if (!glyphSurf)
            throw std::bad_alloc();
        SDL_Texture *glyphTex = SDL_CreateTextureFromSurface(state->renderer, glyphSurf);
        SDL_FreeSurface(glyphSurf);
        if (!glyphTex)
            throw std::bad_alloc();
        state->fontCache[c] = glyphTex;
    }
}
