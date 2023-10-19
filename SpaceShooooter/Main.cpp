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
#include "BackGround.h"
#include "GameUI.h"
#include"GameManager.h"
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
    BackGround background(renderer);
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        // Handle SDL initialization error
    }

    if (TTF_Init() < 0) {
        // Handle SDL_ttf initialization error
    }
    TTF_Font* font = TTF_OpenFont("Asset/Hud/courbi.ttf", 24);
    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    bool quit = false;
    GameManager* gameManager = new GameManager();
    GameManager::GameState state;
    
    PlayerShip* playerShip(new PlayerShip({ 100, 200, 50, 50 }, 10, 0, 0));
    std::vector<Asteroid*> asteroids;
    std::vector<Enemy*> enemies;
    std::vector<Projectile*> projectiles;
    state.playerShip=playerShip;

    

    const Uint8* keystate = SDL_GetKeyboardState(nullptr);// Get the state of the keyboard



    playerShip->LoadData();
    while (!quit) 
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window)) {
                    quit = true;
                }
                break;

            }
        }
        if (keystate[SDL_SCANCODE_GRAVE])
        {
            gameManager->SaveGame(state);
        }
        if (keystate[SDL_SCANCODE_L])
        {
            gameManager->ClearEnemies(enemies);
            gameManager->ClearAsteroids(asteroids);

			gameManager->LoadGame(state);
            for (auto& e : state.enemies) {
                enemies.push_back(e->Clone());
            }
            for (auto& a : state.asteroids) {
				asteroids.push_back(a->Clone());
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
                state.asteroids.push_back(new Asteroid(x, y, size));
            }
        }

        // Randomly generate new enemies
        if (spawnTimer<=0) {
            if (enemies.size() < MAX_ENEMIES && rand() % 100 < 5) {
                int numUFOs = rand() % 2 == 0 ? 1 :3;
                int numShips = rand() % 2 == 0 ? 1 : 3;
                std::vector<Enemy*> newEnemies = EnemyFactory::CreateRandomEnemies(numUFOs, numShips, WINDOW_WIDTH, WINDOW_HEIGHT);
                enemies.insert(enemies.end(), newEnemies.begin(), newEnemies.end());
                state.enemies.insert(state.enemies.end(), newEnemies.begin(), newEnemies.end());
                spawnTimer=100;
                
            }
        }
        else {
            spawnTimer--;
        }
        state.enemies=enemies;
        state.asteroids=asteroids;
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
					enemy->TakeDamage(playerShip->GetDamage());
					projectile->Destroy();
                    playerShip->AddScore(enemy->AwardPoints());
				}
			}
            for (auto& asteroid : asteroids) 
            {
                if (projectile->CheckCollision(asteroid->GetPosition()) && projectile->isPlayerProjectile)
                {
					asteroid->Destroy();
					projectile->Destroy();
                    playerShip->AddScore(asteroid->AwardPoints());
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

        const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);
        playerShip->HandleInput(keyboardState, projectiles);


        playerShip->Update();

        // Check for conditions to stop the game loop
        if (playerShip->IsDestroyed()) {
            quit = true;
        }

        // Clear the screen
 
        SDL_RenderClear(renderer);
        if (rand() % 100 < 5) {
            background.AddStar();
        }

        if (rand() % 100 < 2) {
            background.AddCloud();
        }
        background.MoveObjects();
        background.Render();
        // Render game UI
        
        GameUI::GetInstance().SetLives(playerShip->GetLives());
        GameUI::GetInstance().SetScore(playerShip->GetScore());
        GameUI::GetInstance().Render(renderer);

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
    TTF_Quit();
    SDL_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}


