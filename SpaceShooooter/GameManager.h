#pragma once
#include <vector>
#include "Enemy.h"
#include "PlayerShip.h"
#include "Asteroid.h"
class GameManager
{
private :
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

};

