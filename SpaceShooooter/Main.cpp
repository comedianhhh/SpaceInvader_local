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
#include "EnemyShip.h"
#include "EnemyUFO.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int MAX_ASTEROIDS = 6;
const int MAX_ENEMIES = 3;
int spawnTimer = 1000;
int main(int argc, char* argv[]) {

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    window = SDL_CreateWindow("SDL Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    bool quit = false;
    
    PlayerShip* playerShip(new PlayerShip({ 100, 200, 50, 50 }, 3,0));
    std::vector<Asteroid*> asteroids;
    std::vector<Enemy*> enemies;
    std::vector<Projectile*> projectiles;

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
            int y = -rand() % (WINDOW_HEIGHT - size);
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
        if (spawnTimer<=0) {
            if (enemies.size() < MAX_ENEMIES && rand() % 100 < 5) {
                int numUFOs = rand() % 2 == 0 ? 1 :3;
                int numShips = rand() % 2 == 0 ? 1 : 3;
                std::vector<Enemy*> newEnemies = EnemyFactory::CreateRandomEnemies(numUFOs, numShips, WINDOW_WIDTH, WINDOW_HEIGHT);
                enemies.insert(enemies.end(), newEnemies.begin(), newEnemies.end());
                spawnTimer=100;
            }
        }
        else {
            spawnTimer--;
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
            if (enemy->CheckCollision(playerShip->GetPosition()))
            {
                playerShip->TakeDamage();
                enemy->Destroy();
            }
            if (enemy->GetHealth() <= 0)
            {
                enemy->Destroy();
            }
            if (auto* ship = dynamic_cast<EnemyShip*>(enemy))
            {
                ship->Shoot(projectiles);
            }
            else if (auto* ufo = dynamic_cast<EnemyUFO*>(enemy))
            {

            }
        }
        for (auto& projectile : projectiles)
        {
            projectile->Update();
            if (projectile->CheckCollision(playerShip->GetPosition()) && !projectile->isPlayerProjectile)
            {
                playerShip->TakeDamage();
                projectile->Destroy();
            }
            for(auto&enemy : enemies)
			{
				if (projectile->CheckCollision(enemy->GetPosition()) && projectile->isPlayerProjectile)
				{
					enemy->Destroy();
					projectile->Destroy();
				}
			}
            
            if (projectile->IsOutOfWindow(WINDOW_HEIGHT)) {
                projectile->Destroy();
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

        // Erase destroyed projectiles and deallocate memory
        std::cout << "Number of projectiles before erase: " << projectiles.size() << std::endl;

        // Erase destroyed projectiles and deallocate memory
        projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(), [](Projectile* projectile)
            {
                bool isDestroyed = projectile->IsDestroyed();
                if (isDestroyed)
                {
                    delete projectile;
                }
                return isDestroyed;
            }),
            projectiles.end());

        std::cout << "Number of projectiles after erase: " << projectiles.size() << std::endl;



        std::cout<<projectiles.size()<<std::endl;
        const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);
        playerShip->HandleInput(keyboardState, projectiles);


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
            enemy->Render(renderer);
        }
        for(auto& projectile : projectiles)
		{
			projectile->Render(renderer);
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
