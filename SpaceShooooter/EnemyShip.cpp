#include "EnemyShip.h"
#include <cstdlib>

EnemyShip::EnemyShip(SDL_Rect position, int health, int score)
    : position(position), health(health), score(score), destroyed(false)
{
    shootTimer = 300;
}

EnemyShip::~EnemyShip() {}

void EnemyShip::Update() {
    // Update enemy's position and behavior

    if (!destroyed) {
		if (position.y < 100)
		{
			position.y +=1;
		}
    }
}

void EnemyShip::Render(SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load("Asset/Enemies/enemyShip.png");
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

void EnemyShip::TakeDamage(int amount) {
    // Reduce enemy's health
    health -= amount;

    if (health <= 0)
    {
        Destroy();
    }
}
void EnemyShip::Shoot(std::vector<Projectile*>& projectiles) 
{
    if (shootTimer <= 0) {
        projectiles.push_back(new Projectile(position.x + 20, position.y + 20, 2, false));
        shootTimer = 500;
    }
    if (shootTimer > 0) {
        shootTimer--;
    }
}

void EnemyShip::Destroy() {
    destroyed =true;
}
bool EnemyShip::IsDestroyed() const {
	return destroyed;
}
int EnemyShip::AwardPoints() const {
	return score;
}
SDL_Rect EnemyShip::GetPosition() const {
	return position;
}
int EnemyShip::GetHealth() const {
	return health;
}
int EnemyShip::GetScore() const {
	return score;
}
int EnemyShip::GetY() const {
	return position.y;
}
int EnemyShip::GetX() const {
	return position.x;
}
bool EnemyShip::CheckCollision(const SDL_Rect& otherRect) const {
	return SDL_HasIntersection(&position, &otherRect);
}
void EnemyShip::LoadData() 
{
    std::ifstream inputStream("EnemyShip.json");
    std::string str((std::istreambuf_iterator<char>(inputStream)), std::istreambuf_iterator<char>());
    json::JSON document = json::JSON::Load(str);
    if(document.hasKey("EnemyShip"))
	{
		json::JSON enemyShip = document["EnemyShip"];
		if(enemyShip.hasKey("health"))
		{
			health = enemyShip["health"].ToInt();
		}
		if(enemyShip.hasKey("score"))
		{
			score = enemyShip["score"].ToInt();
		}
	}
}