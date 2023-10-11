#pragma once
#ifndef ASTEROID_H
#define ASTEROID_H

#include "GameObject.h"

class Asteroid : public GameObject {
public:
    Asteroid(SDL_Renderer* renderer, int x, int y, int size);
    void update() override;
    void render() override;


private:
    int size;
};

#endif // ASTEROID_H

