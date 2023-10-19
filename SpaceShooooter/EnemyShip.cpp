#include "EnemyShip.h"
#include <cstdlib>

EnemyShip::EnemyShip(SDL_Rect position, int health, int score)
    : position(position), health(health), score(score), destroyed(false)
{
    shootTimer = 600;
    timer = shootTimer;
    filepath= "Asset/Enemies/enemyShip.png";

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

void EnemyShip::Render(SDL_Renderer* renderer)
{
    SDL_Surface* surface = IMG_Load(filepath.c_str());
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
    if (timer <= 0) {
        projectiles.push_back(new Projectile(position.x + 20, position.y + 20, 2, false));
        timer = shootTimer;
    }
    if (timer > 0) {
        timer--;
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
std::string EnemyShip::GetType() const {
    return "Ship";
}
bool EnemyShip::CheckCollision(const SDL_Rect& otherRect) const {
	return SDL_HasIntersection(&position, &otherRect);
}

void EnemyShip::SetX(int x) 
{
    this->position.x = x;
}
void EnemyShip::SetY(int y) 
{
	this->position.y = y;
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
        if (enemyShip.hasKey("shootTimer")) 
        {
            shootTimer = enemyShip["shootTimer"].ToInt();
        }
        if (enemyShip.hasKey("texture")) 
        {
            filepath= enemyShip["texture"].ToString();
        }
	}
}
Enemy* EnemyShip::Clone() const
{
	return new EnemyShip(*this);
}