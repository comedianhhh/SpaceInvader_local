#include "EnemyShip.h"

EnemyShip::EnemyShip(SDL_Renderer* renderer, int x, int y) : GameObject(renderer, x, y) {
    // Initialize enemy ship
}

void EnemyShip::update() {
    // Update enemy ship logic based on AI and game state
}

void EnemyShip::render() {
    // Render enemy ship graphics
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue color
    SDL_Rect rect = { x, y, 20, 20 }; // Adjust dimensions as needed
    SDL_RenderFillRect(renderer, &rect);
}
