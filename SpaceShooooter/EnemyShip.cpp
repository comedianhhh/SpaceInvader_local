#include "EnemyShip.h"

EnemyShip::EnemyShip(SDL_Rect position, int health, int score)
    : position(position), health(health), score(score) {}

EnemyShip::~EnemyShip() {}

void EnemyShip::Update() {
    // Update enemy's position and behavior
}

void EnemyShip::Render(SDL_Renderer* renderer) {
    // Render enemy on the screen using the SDL_Renderer
}

void EnemyShip::TakeDamage(int amount) {
    // Reduce enemy's health
}

void EnemyShip::Destroy() {
    // Handle enemy destruction
}