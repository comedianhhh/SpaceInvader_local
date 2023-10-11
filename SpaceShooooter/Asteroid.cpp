#include "Asteroid.h"

Asteroid::Asteroid(SDL_Renderer* renderer, int x, int y, int size) : GameObject(renderer, x, y), size(size) {
    // Initialize asteroid
}

void Asteroid::update() {
    // Update asteroid logic based on game state
}

void Asteroid::render() {
    // Render asteroid graphics
}
