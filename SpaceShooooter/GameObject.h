#pragma once

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL.h>

class GameObject {
public:
    GameObject(SDL_Renderer* renderer, int x, int y);
    virtual ~GameObject();

    virtual void update() = 0;
    virtual void render() = 0; 

    SDL_Texture* getTexture() const;
protected:
    SDL_Renderer* renderer;
    int x;
    int y;
    SDL_Texture* texture;
};

#endif // GAMEOBJECT_H

