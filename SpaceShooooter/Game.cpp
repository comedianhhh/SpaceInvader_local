#include "Game.h"

Game::Game() : playerShip(nullptr),window(nullptr), renderer(nullptr)
{
    playerShip = new PlayerShip(renderer, 0, 0);
    //TODO: Initialize SDL
    //TODO: Create window and renderer

}

Game::~Game() {
    delete playerShip;

    for (EnemyShip* enemyShip : enemyShips) {
        delete enemyShip;
    }

    for (Asteroid* asteroid : asteroids) {
        delete asteroid;
    }

}

void Game::run() {
    while (true) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            handleInput(event);
        }

        updateGame();
        render();

    }
}

void Game::handleInput(SDL_Event& event) {
    switch (event.type) {
    case SDL_QUIT:
        break;

    case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
        case SDLK_w:
            playerShip->moveUp();
            break;

        case SDLK_a:
            playerShip->moveLeft();
            break;

        case SDLK_s:
            playerShip->moveDown();
            break;

        case SDLK_d:
            playerShip->moveRight();
            break;

        case SDLK_SPACE:
            playerShip->shoot();
            break;
        }
        break;

    case SDL_KEYUP:
        switch (event.key.keysym.sym) {
        case SDLK_w:

            break;

        case SDLK_a:

            break;

        case SDLK_s:

            break;

        case SDLK_d:

            break;
        }
        break;

    default:
        break;
    }
}
void Game::updateGame() {
    // Update game logic
}

void Game::render() {

    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);

}
void Game::spawnEnemyShip() {
 
    EnemyShip* newEnemyShip = new EnemyShip(renderer, 1, 1);
    enemyShips.push_back(newEnemyShip);
}
void Game::spawnAsteroid() {
	Asteroid* newAsteroid = new Asteroid(renderer, 1, 1, 1);
	asteroids.push_back(newAsteroid);
}

void Game::checkCollisions() {

    // Check collisions between playerShip and asteroids/enemyShips
    // Handle scoring, player deaths
}

void Game::resetGame() {
    // reset player and enemy positions, scores, etc.
}