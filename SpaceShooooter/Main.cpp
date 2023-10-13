#include <SDL.h>
#include <SDL_image.h>
#include "PlayerShip.h"
#include "Asteroid.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int main(int argc, char* argv[]) {

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    window = SDL_CreateWindow("SDL Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    bool quit = false;
    
    PlayerShip* playerShip(new PlayerShip({ 100, 100, 50, 50 }, 3));
    std::vector<Asteroid*> asteroids;

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
        if (rand() % 100 < 5) {
            int size = rand() % 2 == 0 ? 30 : 50; // Randomly select asteroid size
            int y = rand() % (WINDOW_HEIGHT - size); // Randomly select asteroid position
            asteroids.push_back(new Asteroid(WINDOW_WIDTH, y, size));
            //debug 
            std::cout << "New asteroid created at (" << WINDOW_WIDTH << ", " << y << ") with size " << size << std::endl;
        }

        // Update asteroids
        for (auto& asteroid : asteroids) {
            asteroid->Update();
        }

        // Erase destroyed asteroids and deallocate memory
        asteroids.erase(std::remove_if(asteroids.begin(), asteroids.end(), [](Asteroid* asteroid) {
            bool isDestroyed = asteroid->IsDestroyed();
            if (isDestroyed) {
                delete asteroid;
            }
            return isDestroyed;
            }), asteroids.end());




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