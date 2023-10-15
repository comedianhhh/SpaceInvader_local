#include "Projectile.h"
#include <iostream>

Projectile::Projectile(int x, int y, int velocity, bool isPlayerProjectile) :posX(x), posY(y), velocity(velocity), isPlayerProjectile(isPlayerProjectile), destroyed(false)
{
	rect.x = posX;
	rect.y = posY;
	rect.w = 9;
	rect.h = 54;
}
        

void Projectile::Update()
{
   rect.y += velocity;
}

void Projectile::Render(SDL_Renderer* renderer)
{
    if (!isPlayerProjectile) {
        SDL_Surface* surface = IMG_Load("Asset/Enemies/laserRed.png");
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
    else if (isPlayerProjectile) {
		SDL_Surface* surface = IMG_Load("Asset/Mainplayer/laserGreen.png");
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

}
bool Projectile::CheckCollision(const SDL_Rect& otherRect) const {
    if (!destroyed) {
        return SDL_HasIntersection(&rect, &otherRect);
    }
    return false;
}
void Projectile::Destroy() 
{
    destroyed = true;
}
bool Projectile::IsDestroyed() const {
	return destroyed;
}
SDL_Rect Projectile::GetPosition() const {
	return rect;
}
int Projectile::GetY() const {
	return posY;
}
