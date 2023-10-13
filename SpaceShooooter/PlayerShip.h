#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H


#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
class PlayerShip {
public:
    PlayerShip(SDL_Rect initialPosition, int initialLives);
    ~PlayerShip();

    void HandleInput(const Uint8* keyboardState);
    void Update();
    void Render(SDL_Renderer* renderer);
    void TakeDamage();
    bool IsDestroyed() const;
    void Reset();

private:
    SDL_Rect position;
    int lives;
    
};

#endif // PLAYERSHIP_H
