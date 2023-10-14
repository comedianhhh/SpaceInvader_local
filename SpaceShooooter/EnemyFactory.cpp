#include "EnemyFactory.h"
#include "EnemyShip.h"
#include "EnemyUFO.h"
Enemy* EnemyFactory::CreateEnemy(EnemyType type, SDL_Rect pos,int h,int s)
{
	switch (type)
	{
	case EnemyFactory::UFO:
		return new EnemyUFO(pos,h,s);
		break;
	case EnemyFactory::SHIP:
		return new EnemyShip(pos,h,s);
		break;
	default:
		break;
	}
	return nullptr;
}