#include "GameUI.h"

GameUI* GameUI::instance = nullptr;

void GameUI::SetLives(int lives)
{
	this->lives = lives;
}
void GameUI::IncreaseScore(int score)
{
	this->score += score;
}
void GameUI::Render(SDL_Renderer* renderer)
{
	TTF_Font* font = TTF_OpenFont("Asset/Hud/courbi.ttf", 24);
	RenderText(renderer, font, "Score: " + std::to_string(score), 20, 20);
	RenderText(renderer, font, "Lives: " + std::to_string(lives), 700, 20);

	SDL_Surface* surface = IMG_Load("Asset/Hud/life.png");
	if (!surface) {
		// Error handling if the image cannot be loaded
		SDL_Log("Failed to load image: %s", IMG_GetError());
		return;
	}

	SDL_Texture* livesTexture = SDL_CreateTextureFromSurface(renderer, surface);
	
	SDL_FreeSurface(surface);

	SDL_RenderCopy(renderer, livesTexture, nullptr, &position);

	SDL_DestroyTexture(livesTexture);



}
void GameUI::RenderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y) 
{
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), { 255,255,255 });
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_Rect destRect = { x, y, 20,20};
	SDL_RenderCopy(renderer, texture, nullptr, &destRect);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}