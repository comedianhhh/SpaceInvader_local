#pragma once

#ifndef ENEMYSHIP_H
#define ENEMYSHIP_H

#include <SDL.h>

class EnemyShip{
public:
    EnemyShip(SDL_Rect position, int health, int score);
    virtual ~EnemyShip();

    virtual void Update();
    virtual void Render(SDL_Renderer* renderer);
    virtual void TakeDamage(int amount);
    virtual void Destroy();

protected:
    SDL_Rect position;
    int health;
    int score;
};

#endif
