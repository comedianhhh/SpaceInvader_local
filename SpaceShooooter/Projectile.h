#pragma once
#ifndef _PROJECTILE_H_
#define _PROJECTILE_H_
#include <SDL.h>
#include <SDL_image.h>
class Projectile
{
public:
    Projectile(int x, int y, int velocity, bool isPlayerProjectile);

    void Update();
    void Render(SDL_Renderer* renderer);
    bool CheckCollision(const SDL_Rect& otherRect) const;
    bool IsDestroyed() const;
    int GetX() const;
    int GetY() const;

    void Destroy();
    SDL_Rect GetPosition() const;
    bool isPlayerProjectile;
    bool IsOutOfWindow(int windowHeight) const;

private:
    int posX;
    int posY;
    int velocity;
    bool destroyed;
    SDL_Rect rect;
};
#endif // !_PROJECTILE_H_
