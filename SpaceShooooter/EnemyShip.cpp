#include "EnemyShip.h"
#include <cstdlib>

EnemyShip::EnemyShip(SDL_Rect position, int health, int score)
    : position(position), health(health), score(score), destroyed(false)
{
    shootTimer = 0;
}

EnemyShip::~EnemyShip() {}

void EnemyShip::Update() {
    // Update enemy's position and behavior

    if (!destroyed) {
		if (position.y < 100)
		{
	
			position.y +=1;
		}
    }
}

void EnemyShip::Render(SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load("Asset/Enemies/enemyShip.png");
    if (!surface) {
        // Error handling if the image cannot be loaded
        SDL_Log("Failed to load image: %s", IMG_GetError());
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    SDL_RenderCopy(renderer, texture, nullptr, &position);

    SDL_DestroyTexture(texture);

}

void EnemyShip::TakeDamage(int amount) {
    // Reduce enemy's health
    health -= amount;

    if (health <= 0)
    {
        Destroy();
    }
}
Projectile* EnemyShip::Shoot() {
	// Return a new projectile
	return new Projectile(position.x, position.y,2,false);
}

void EnemyShip::Destroy() {
    // Handle enemy destruction
}
bool EnemyShip::IsDestroyed() const {
	// Return true if enemy is destroyed
	return health <= 0;
}
int EnemyShip::AwardPoints() const {
	// Return the points awarded for destroying this enemy
	return score;
}
SDL_Rect EnemyShip::GetPosition() const {
	// Return the enemy's position
	return position;
}
int EnemyShip::GetHealth() const {
	return health;
}
int EnemyShip::GetScore() const {
	return score;
}
int EnemyShip::GetY() const {
	return position.y;
}
int EnemyShip::GetX() const {
	return position.x;
}
bool EnemyShip::CheckCollision(const SDL_Rect& otherRect) const {
	return SDL_HasIntersection(&position, &otherRect);
}