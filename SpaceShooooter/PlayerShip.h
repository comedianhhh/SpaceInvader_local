#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H


#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Projectile.h"
#include<vector>
class PlayerShip {
public:
    PlayerShip(SDL_Rect initialPosition, int initialLives,int shootTimer);
    ~PlayerShip();

    void HandleInput(const Uint8* keyboardState,std::vector<Projectile*>& projectiles);
    void Update();
    void Render(SDL_Renderer* renderer);
    void TakeDamage();
    bool IsDestroyed() const;
    void Reset();
    SDL_Rect GetPosition()const;
    Projectile* Shoot();

private:
    SDL_Rect position;
    int lives;
    int shootTimer;
    
};

#endif // PLAYERSHIP_H
