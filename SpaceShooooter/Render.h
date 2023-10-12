#pragma once
#ifndef RENDER_H
#define RENDER_H

#include <SDL.h>
#include <SDL_image.h>


class Render {
public:
    Render(SDL_Renderer* renderer);
    ~Render();

    SDL_Texture* loadTexture(const char* path);
    void renderTexture(SDL_Texture* texture, int x, int y);

private:
    SDL_Renderer* renderer;
};

#endif // RENDER_H
