#include <SDL.h>
#include <SDL_image.h>
#include "PlayerShip.h"
#include "Asteroid.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include"EnemyFactory.h"
#include "Projectile.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int MAX_ASTEROIDS = 6;

int main(int argc, char* argv[]) {

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    window = SDL_CreateWindow("SDL Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    bool quit = false;
    
    PlayerShip* playerShip(new PlayerShip({ 100, 200, 50, 50 }, 3));
    std::vector<Asteroid*> asteroids;
    std::vector<Enemy*> enemies;


    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window)) {
                    quit = true;
                }
                break;
                // Handle other event types as needed
            }
        }


        // Randomly generate new asteroids
        if (asteroids.size() < MAX_ASTEROIDS && rand() % 100 < 5) {
            int size = rand() % 2 == 0 ? 30 : 50; 

            int x = rand() % (WINDOW_WIDTH - size); 
            int y = -rand()%(WINDOW_HEIGHT-size);
            bool overlap = false;
            for (const auto& asteroid : asteroids) {
                if (abs(asteroid->GetX() - x) < size && abs(asteroid->GetY() - y) < size) {
                    overlap = true;
                    break;
                }
            }

            if (!overlap) {
                asteroids.push_back(new Asteroid(x, y, size));
            }
        }

        // Randomly generate new enemies
        if (enemies.size() < 5 && rand() % 100 < 5) {
			int size = rand() % 2 == 0 ? 30 : 50;

			int x = rand() % (WINDOW_WIDTH - size);
			int y = -rand() % (WINDOW_HEIGHT - size);

            Enemy* enemyShip = EnemyFactory::CreateEnemy(EnemyFactory::EnemyType::SHIP, { x, y, 50, 50 }, 3, 10);
            enemies.push_back(enemyShip);
		}
            
        // Update asteroids
        for (auto& asteroid : asteroids) {
            asteroid->Update();
            if (asteroid->CheckCollision(playerShip->GetPosition())) {
				playerShip->TakeDamage();
				asteroid->Destroy();
			}
            if (asteroid->GetY() > WINDOW_HEIGHT)
            {
				asteroid->Destroy();
			}

        }
        for (auto& enemy : enemies) {
			enemy->Update();
            if (enemy->CheckCollision(playerShip->GetPosition())) {
				playerShip->TakeDamage();
				enemy->Destroy();
			}
            if (enemy->GetY() > WINDOW_HEIGHT)
            {
				enemy->Destroy();
			}

		}
        for (auto& enemy : enemies)
        {
            if (enemy->CheckCollision(playerShip->GetPosition()))
            {
				playerShip->TakeDamage();
				enemy->Destroy();
			}
        }


        // Erase destroyed asteroids and deallocate memory
        asteroids.erase(std::remove_if(asteroids.begin(), asteroids.end(), [](Asteroid* asteroid) 
            {
            bool isDestroyed = asteroid->IsDestroyed();
            if (isDestroyed) 
            {
                delete asteroid;
            }
            return 
                isDestroyed;
            }), 
            asteroids.end());

        // Erase destroyed enemies and deallocate memory
        enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](Enemy* enemy)
            {
			bool isDestroyed = enemy->IsDestroyed();
            if (isDestroyed)
            {
				delete enemy;
			}
			return
				isDestroyed;
			}),
            enemies.end());




        const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);
        playerShip->HandleInput(keyboardState);


        playerShip->Update();

        // Check for conditions to stop the game loop
        if (playerShip->IsDestroyed()) {
            quit = true;
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Render player ship
        playerShip->Render(renderer);
        for (const auto& asteroid : asteroids) {
            asteroid->Render(renderer);
        }
        for (const auto& enemy : enemies)
        {
            enemy->Update();
            enemy->Render(renderer);
        }


        // Update the screen with the rendered content
        SDL_RenderPresent(renderer);
    }

    // Cleanup and shutdown SDL

    delete playerShip;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
