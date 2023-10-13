#include "PlayerShip.h"

PlayerShip::PlayerShip(SDL_Rect initialPosition, int live)
    : position(initialPosition), lives(live) {

}

PlayerShip::~PlayerShip() {}

void PlayerShip::HandleInput(const Uint8* keyboardState) 
{
    int adjustedSpeed = 1;

    if (keyboardState[SDL_SCANCODE_W]) {
        position.y -= adjustedSpeed;
    }
    if (keyboardState[SDL_SCANCODE_S]) {
        position.y += adjustedSpeed;
    }
    if (keyboardState[SDL_SCANCODE_A]) {
        position.x -= adjustedSpeed;
    }
    if (keyboardState[SDL_SCANCODE_D]) {
        position.x += adjustedSpeed;
    }
}

void PlayerShip::Update() {
}

void PlayerShip::Render(SDL_Renderer* renderer) {

    SDL_Surface* surface = IMG_Load("Asset/Mainplayer/player.png");
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

void PlayerShip::TakeDamage() {
    lives--;
}

bool PlayerShip::IsDestroyed() const {

    return lives <= 0;
}

void PlayerShip::Reset() {
    lives = 3;
}