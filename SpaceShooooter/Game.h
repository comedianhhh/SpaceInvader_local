#pragma once
#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "Asteroid.h"
#include "PlayerShip.h"
#include "EnemyShip.h"
#include <vector>

class Game {
public:
    Game();
    ~Game();

    void run();

private:
    void handleInput(SDL_Event& event);
    void updateGame();
    void render();

    void spawnAsteroid();
    void spawnEnemyShip();
    void checkCollisions();
    void resetGame();

    SDL_Window* window;
    SDL_Renderer* renderer;


    PlayerShip* playerShip;

    std::vector<EnemyShip*> enemyShips;

    std::vector<Asteroid*> asteroids;

};

#endif // GAME_H
