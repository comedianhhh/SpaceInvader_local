#pragma once
#ifndef _GAMEUI_H_
#define _GAMEUI_H_
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
class GameUI
{
public:	
	inline static GameUI& GetInstance()
	{
		if (!instance)
		{
			instance = new GameUI();
		}
		return *instance;

	}
	inline void Destroy()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	}
	void SetLives(int lives);
	void IncreaseScore(int score);
	void Render(SDL_Renderer* renderer);
	void RenderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y);

private:

	static GameUI* instance;

	int lives=3;
	int score=0;
	SDL_Rect position = { 700,20,20,20 };


	inline explicit GameUI()=default;
	inline ~GameUI()=default;
	GameUI(const GameUI& other) = delete;
	GameUI(GameUI&& other) = delete;
};
#endif // !GameUI


