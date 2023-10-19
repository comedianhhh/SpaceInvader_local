#include "GameUI.h"

GameUI* GameUI::instance = nullptr;

void GameUI::SetLives(int lives)
{
	this->lives = lives;
}
void GameUI::SetScore(int score)
{
	this->score = score;
}
void GameUI::SetHigh(int highscore)
{
	this->highscore = highscore;
}


void GameUI::Render(SDL_Renderer* renderer)
{
	TTF_Font* font = TTF_OpenFont("Asset/Hud/courbi.ttf", 24);
	RenderText(renderer, font, "   Score  : " + std::to_string(score), 20, 40);
	RenderText(renderer, font,"Lives:"+std::to_string(lives), 600, 20);
	RenderText(renderer, font, "Highscore: " + std::to_string(highscore), 20, 60);

	SDL_Surface* surface = IMG_Load("Asset/Hud/life.png");

	SDL_Texture* livesTexture = SDL_CreateTextureFromSurface(renderer, surface);
	
	SDL_FreeSurface(surface);

	SDL_RenderCopy(renderer, livesTexture, nullptr, &position);

	SDL_DestroyTexture(livesTexture);
}
void GameUI::RenderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y) 
{
	if (!font) {
		// Error handling if the image cannot be loaded
		SDL_Log("Failed to load font: %s", TTF_GetError());
	}
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), { 255,255,255 });

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_Rect destRect = { x, y, 100,30};
	SDL_FreeSurface(surface);
	SDL_RenderCopy(renderer, texture, nullptr, &destRect);
	SDL_DestroyTexture(texture);
}