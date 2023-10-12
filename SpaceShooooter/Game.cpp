#include "Game.h"

Game::Game() : playerShip(nullptr),window(nullptr), renderer(nullptr)
{

}

Game::~Game() 
{
    resetGame();
	SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::run() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return;
    }

    window = SDL_CreateWindow("Space Shooter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_Log("Unable to create window: %s", SDL_GetError());
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("Unable to create renderer: %s", SDL_GetError());
        return;
    }

    playerShip = new PlayerShip(renderer,0,0);

    // Game loop
    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }

            handleInput(e);
        }

        updateGame();
        render();

        SDL_RenderPresent(renderer);
    }
    resetGame();
}

void Game::handleInput(SDL_Event& event) {
    switch (event.type) {
    case SDL_QUIT:
        break;

    case SDL_KEYDOWN:
        switch (event.key.keysym.sym) 
        {
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
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
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


    delete playerShip;
    playerShip = nullptr;

    for (auto& enemyShip : enemyShips) {
        delete enemyShip;
    }
    enemyShips.clear();

    for (auto& asteroid : asteroids) {
        delete asteroid;
    }
    asteroids.clear();
}