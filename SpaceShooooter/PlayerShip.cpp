#include "PlayerShip.h"

PlayerShip::PlayerShip(SDL_Renderer* renderer, int x, int y) : GameObject(renderer, x, y) {

}

void PlayerShip::update() {

}

void PlayerShip::render() {

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); 
    SDL_Rect rect = { x, y, 20, 20 }; 
    SDL_RenderFillRect(renderer, &rect);
}
void PlayerShip::moveUp() {
}

void PlayerShip::moveLeft() {
}

void PlayerShip::moveDown() {
}

void PlayerShip::moveRight() {
}

void PlayerShip::stopMovingUp() {
}

void PlayerShip::stopMovingLeft() {
}

void PlayerShip::stopMovingDown() {
}

void PlayerShip::stopMovingRight() {
}

void PlayerShip::shoot() {
}