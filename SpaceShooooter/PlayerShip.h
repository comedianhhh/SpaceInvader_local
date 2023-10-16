#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H


#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Projectile.h"
#include"json.hpp"
#include<vector>
#include<fstream>
class PlayerShip {
public:
    PlayerShip(SDL_Rect initialPosition, int initialLives,int shootTimer,int score);
    ~PlayerShip();

    void HandleInput(const Uint8* keyboardState,std::vector<Projectile*>& projectiles);
    void Update();
    void Render(SDL_Renderer* renderer);
    void TakeDamage();
    bool IsDestroyed() const;
    void Reset();
    int GetLives() const;
    int GetScore() const;
    int GetDamage() const;
    SDL_Rect GetPosition()const;
    Projectile* Shoot();
    void AddScore(int score);
    void LoadData();

private:
    
    SDL_Rect position;
    int damage;
    int lives;
    int shootTimer;
    int score;
    int timer;
    std::string filepath;
    SDL_Texture* texture;
};

#endif // PLAYERSHIP_H
