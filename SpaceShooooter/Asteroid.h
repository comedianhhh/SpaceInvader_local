#pragma once
#ifndef ASTEROID_H
#define ASTEROID_H
#include <SDL.h>
#include <SDL_image.h>
class Asteroid {
private:
    int x;
    int y;
    int size;
    bool destroyed;
    SDL_Rect rect;
public:
    Asteroid(int initialX, int initialY, int initialSize);

    int GetX() const;
    int GetY() const;
    SDL_Rect GetPosition() const;
    int GetSize() const;
    bool IsDestroyed() const;
    void SetX(int x);
    void SetY(int y);   
    void SetSize(int size);
    void Update();
    void Destroy();
    bool CheckCollision(const SDL_Rect& otherRect) const;
    int AwardPoints() const;
    void Render(SDL_Renderer* renderer);
    Asteroid* Clone() const;
};

#endif // ASTEROID_H

