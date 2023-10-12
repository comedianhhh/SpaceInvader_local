#include "EnemyShip.h"
#include"Render.h"
EnemyShip::EnemyShip(SDL_Renderer* renderer, int x, int y) : GameObject(renderer, x, y) {
    Render rendererInstance(renderer);
    texture = rendererInstance.loadTexture("assets/Enemies/enemyShip.png");
}

void EnemyShip::update() {
    // Update enemy ship logic based on AI and game state
}

void EnemyShip::render() {
    Render rendererInstance(renderer);
    rendererInstance.renderTexture(texture, x, y);

}
