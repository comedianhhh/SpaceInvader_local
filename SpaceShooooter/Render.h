#pragma once
#ifndef RENDER_H
#define RENDER_H

#include <SDL.h>
#include "GameObject.h"

class Render {
public:
    Render(SDL_Renderer* renderer);
    ~Render();

    void renderGameObject(GameObject& gameObject);

private:
    SDL_Renderer* renderer;
};

#endif // RENDER_H
