#pragma once
#ifndef _ENEMY_H
#define _ENEMY_H
#include <SDL.h>
#include <SDL_image.h>
#include "Projectile.h"
#include<vector>
#include"json.hpp"
#include<fstream>
class Enemy 
{
public :
	virtual ~Enemy() {};
	virtual void Update() = 0;
	virtual void Render(SDL_Renderer* renderer) = 0;
	virtual void TakeDamage(int amount) = 0;
	virtual void Destroy() = 0;
	virtual int AwardPoints() const = 0;
	virtual bool IsDestroyed() const = 0;
	virtual SDL_Rect GetPosition() const = 0;
	virtual int GetHealth() const = 0;
	virtual int GetScore() const = 0;
	virtual int GetY() const = 0;
	virtual int GetX() const = 0;
	virtual std::string GetType() const = 0;
	virtual void SetY(int y) = 0;
	virtual void SetX(int x) = 0;
	virtual bool CheckCollision(const SDL_Rect& otherRect) const = 0;
	virtual void LoadData() = 0;
	virtual Enemy* Clone() const = 0;
	

};


#endif // !_ENEMY_H

