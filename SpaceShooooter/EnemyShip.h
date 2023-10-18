#pragma once

#ifndef ENEMYSHIP_H
#define ENEMYSHIP_H
#include "Enemy.h"
#include "Projectile.h"
class EnemyShip:public Enemy{
public:
    EnemyShip(SDL_Rect position, int health, int score);
    virtual ~EnemyShip();

    void Update() override;
    void Render(SDL_Renderer* renderer) override;
    void TakeDamage(int amount) override;
    void Destroy() override;
    bool IsDestroyed() const;
    int AwardPoints() const override;
    SDL_Rect GetPosition() const override;
    int GetHealth() const override;
    int GetScore() const override;
    int GetY() const override;
    int GetX() const override;
    std::string GetType() const override;
    bool CheckCollision(const SDL_Rect& otherRect) const;
    void Shoot(std::vector<Projectile*>& projectiles);
    void SetX(int x) override;
    void SetY(int y) override;
    void LoadData() override;
    Enemy* Clone() const override;
protected:
    SDL_Rect position;
    int shootTimer;
    int health;
    int score;
    bool destroyed;
    int timer;
    std::string filepath;
    SDL_Texture* texture;

};

#endif
