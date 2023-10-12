#include "PlayerShip.h"
#include "Render.h"
PlayerShip::PlayerShip(SDL_Renderer* renderer, int x, int y) : GameObject(renderer, x, y) {
    Render rendererInstance(renderer);
    texture = rendererInstance.loadTexture("assets/Mainplayer/player.png");
}

void PlayerShip::update() {

}

void PlayerShip::render() {
    Render rendererInstance(renderer);
    rendererInstance.renderTexture(texture, x, y);
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