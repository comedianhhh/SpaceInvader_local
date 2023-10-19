#pragma once
#include <vector>
#include "Enemy.h"
#include "PlayerShip.h"
#include "Asteroid.h"
#include "EnemyFactory.h"
#include"EnemyShip.h"
#include"EnemyUFO.h"
class GameManager
{
public :
	struct GameState
	{

		PlayerShip* playerShip;
		std::vector<Enemy*> enemies;
		std::vector<Asteroid*> asteroids;

	};

public :
	GameManager();
	~GameManager();
	void SaveGame(const GameState& state);
	void LoadGame(GameState& state);
	void ClearEnemies(std::vector<Enemy*>& enemies);
	void ClearAsteroids(std::vector<Asteroid*>& asteroids);
};

