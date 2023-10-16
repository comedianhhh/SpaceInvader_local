#include "GameManager.h"

#include <fstream>

GameManager::GameManager() {}

GameManager::~GameManager() {}

void GameManager::SaveGame(const GameState& state) {

	std::ofstream file("savegame.dat", std::ios::binary);

	// Save player ship
	file.write((char*)state.playerShip, sizeof(PlayerShip));

	// Save number of enemies
	int numEnemies = state.enemies.size();
	file.write((char*)&numEnemies, sizeof(int));

	// Save each enemy
	for (Enemy* enemy : state.enemies) {
		file.write((char*)enemy, sizeof(Enemy));
	}

	// Save asteroids
	for(Asteroid* asteroid : state.asteroids) 
	{
		file.write((char*)asteroid, sizeof(Asteroid));
	}

	file.close();

}

void GameManager::LoadGame(GameState& state) {

	std::ifstream file("savegame.dat", std::ios::binary);

	// Load player ship
	file.read((char*)&state.playerShip, sizeof(PlayerShip));

	// Load number of enemies
	int numEnemies;
	file.read((char*)&numEnemies, sizeof(int));

	// Load enemies
	state.enemies.resize(numEnemies);
	for (int i = 0; i < numEnemies; i++) 
	{
		file.read((char*)&state.enemies[i], sizeof(Enemy));
	}
	int numAsteroids;

	state.asteroids.resize(numAsteroids);
	for (int i = 0; i < numAsteroids; i++)
	{
		file.read((char*)&state.asteroids[i], sizeof(Asteroid));
	}

	file.close();

}