#pragma once
#ifndef ENEMYFACTORY
#define ENEMYFACTORY
#include "Enemy.h"
class EnemyFactory
{
public:
	static std::vector<Enemy*> CreateRandomEnemies(int numUFOs, int numShips, int windowWidth, int windowHeight);

};

#endif // !ENEMYFACTORY


