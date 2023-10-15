#include "EnemyUFO.h"
bool moveright = true;
EnemyUFO::EnemyUFO(SDL_Rect position, int health, int score)
	: position(position), health(health), score(score), destroyed(false){}

EnemyUFO::~EnemyUFO()
{
}
void EnemyUFO::Update()
{

	if (!destroyed) 
	{
		if (moveright) {
			position.x += 1;
		}
		else {
			position.x -= 1;
		}

		if (position.x > 750 && moveright) {
			moveright = false;
		}
		if (position.x < 50) {
			moveright = true;
		}
		position.y += 1;
	}
}
void EnemyUFO::Render(SDL_Renderer* renderer)
{
	SDL_Surface* surface = IMG_Load("Asset/Enemies/enemyUFO.png");
	if (!surface) {
		// Error handling if the image cannot be loaded
		SDL_Log("Failed to load image: %s", IMG_GetError());
		return;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	SDL_RenderCopy(renderer, texture, nullptr, &position);

	SDL_DestroyTexture(texture);

}
void EnemyUFO::TakeDamage(int amount)
{
	health -= amount;
	if (health <= 0)
	{
		Destroy();
	}
}
void EnemyUFO::Destroy()
{
	destroyed= true;
}
int EnemyUFO::AwardPoints() const
{
	return score;
}
bool EnemyUFO::IsDestroyed() const
{
	return destroyed;
}
SDL_Rect EnemyUFO::GetPosition() const
{
	return position;
}
int EnemyUFO::GetHealth() const
{
	return health;
}
int EnemyUFO::GetScore() const
{
	return score;
}
int EnemyUFO::GetY() const
{
	return position.y;
}
int EnemyUFO::GetX() const
{
	return position.x;
}
bool EnemyUFO::CheckCollision(const SDL_Rect& otherRect) const
{
	return SDL_HasIntersection(&position, &otherRect);
}


