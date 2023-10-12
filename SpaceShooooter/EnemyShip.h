#pragma once

#ifndef ENEMYSHIP_H
#define ENEMYSHIP_H

#include "GameObject.h"

class EnemyShip : public GameObject {
public:
    EnemyShip(SDL_Renderer* renderer, int x, int y);
    void update() override;
    void render() override;

private:

};

#endif
