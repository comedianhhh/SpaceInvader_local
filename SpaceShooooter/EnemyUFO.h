#pragma once
#ifndef _ENEMYUFO_H
#define _ENEMYUFO_H
#include "Enemy.h"
class EnemyUFO:public Enemy
{
public:
    EnemyUFO(SDL_Rect position, int health, int score);
    virtual ~EnemyUFO();

    void Update() override;
    void Render(SDL_Renderer* renderer) override;
    void TakeDamage(int amount) override;
    void Destroy() override;
    int AwardPoints() const override;
    bool IsDestroyed() const ;
    SDL_Rect GetPosition() const override;
    int GetHealth() const override;
    int GetScore() const override;
    int GetY() const override;
    int GetX() const override;
    bool CheckCollision(const SDL_Rect& otherRect) const;
    void LoadData() override;

protected:
    SDL_Rect position;
    int health;
    int score;
    bool destroyed;
};

#endif // !_ENEMYUFO_H