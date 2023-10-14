#include "Asteroid.h"

Asteroid::Asteroid(int initialX, int initialY, int initialSize)
    : x(initialX), y(initialY), size(initialSize), destroyed(false)
{
    rect.x = x;
    rect.y = y;
    rect.w = size;
    rect.h = size;
}

int Asteroid::GetX() const {
    return x;
}

int Asteroid::GetY() const {
    return y;
}

int Asteroid::GetSize() const {
    return size;
}

bool Asteroid::IsDestroyed() const {
    return destroyed;
}

void Asteroid::Update() {
    if (!destroyed) {
        y += 1;
        rect.y = y;
    }
}

void Asteroid::Destroy() {

    destroyed = true;
}

bool Asteroid::CheckCollision(const SDL_Rect& otherRect) const {
    if (!destroyed) {
        return SDL_HasIntersection(&rect, &otherRect);
    }
    return false;
}

int Asteroid::AwardPoints() const {
    if (size == 50) {
        return 10;
    }
    else if (size == 30) {
        return 5;
    }
    else {
        return 3;
    }
}
void Asteroid::Render(SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load("Asset/Asteroids/meteorBig.png");
    if (!surface) {
        // Error handling if the image cannot be loaded
        SDL_Log("Failed to load image: %s", IMG_GetError());
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);  

    SDL_RenderCopy(renderer, texture, nullptr, &rect);

    SDL_DestroyTexture(texture);

}