#pragma once
#ifndef ENEMYFACTORY
#define ENEMYFACTORY
#include "Enemy.h"
class EnemyFactory
{
public:
	enum EnemyType
	{
		UFO,
		SHIP
	};
	static Enemy* CreateEnemy(EnemyType type,SDL_Rect pos,int health,int score);

};

#endif // !ENEMYFACTORY


