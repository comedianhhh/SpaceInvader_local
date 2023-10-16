#include "EnemyFactory.h"
#include "EnemyShip.h"
#include "EnemyUFO.h"
#include <ctime>

std::vector<Enemy*> EnemyFactory::CreateRandomEnemies(int numUFOs, int numShips, int windowWidth, int windowHeight) {
    std::vector<Enemy*> enemies;
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    const int minDistance =  50;
    const int maxAttempts = 5;

    for (int i = 0; i < numUFOs; ++i) {
        int x, y;
        for (int attempt = 0; attempt < maxAttempts; ++attempt) {
            x = rand() % windowWidth;
            y = -rand() % 100;
            bool overlap = false;
            for (const auto& enemy : enemies) {
                if (std::abs(enemy->GetX() - x) < minDistance) {
                    overlap = true;
                    break;
                }
            }
            if (!overlap) {
                break; 
            }
        }
        EnemyUFO* ufo = new EnemyUFO({ x, y, 50, 50 }, 3, 10);
        ufo->LoadData();
        enemies.push_back(ufo);
    }

    for (int i = 0; i < numShips; ++i) {
        int x, y;
        for (int attempt = 0; attempt < maxAttempts; ++attempt) {
            x = rand() % windowWidth;
            y = -rand() % 100;
            bool overlap = false;
            for (const auto& enemy : enemies) {
                if (std::abs(enemy->GetX() - x) < minDistance) {
                    overlap = true;
                    break;
                }
            }
            if (!overlap) {
                break;
            }
        }
        EnemyShip* ship = new EnemyShip({ x, y, 50, 50 }, 5, 10);
        ship->LoadData();
        enemies.push_back(ship);
    }


    return enemies;
}