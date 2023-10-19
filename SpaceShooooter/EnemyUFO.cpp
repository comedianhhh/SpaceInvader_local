#include "EnemyUFO.h"
bool moveright = true;
EnemyUFO::EnemyUFO(SDL_Rect position, int health, int score)
	: position(position), health(health), score(score), destroyed(false)
{
	filepath = "Asset/Enemies/enemyUFO.png";
}

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
	SDL_Surface* surface = IMG_Load(filepath.c_str());

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
void EnemyUFO::SetX(int x)
{
	position.x = x;
}
void EnemyUFO::SetY(int y)
{
	position.y = y;
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
std::string EnemyUFO::GetType() const
{
	return "UFO";
}
bool EnemyUFO::CheckCollision(const SDL_Rect& otherRect) const
{
	return SDL_HasIntersection(&position, &otherRect);
}
void EnemyUFO::LoadData()
{
	std::ifstream inputStream("EnemyUFO.json");
	std::string str((std::istreambuf_iterator<char>(inputStream)), std::istreambuf_iterator<char>());
	json::JSON document = json::JSON::Load(str);
	if (document.hasKey("EnemyUFO"))
	{
		json::JSON enemyUFO = document["EnemyUFO"];
		if (enemyUFO.hasKey("health"))
		{
			health = enemyUFO["health"].ToInt();
		}

		if (enemyUFO.hasKey("score"))
		{
			score = enemyUFO["score"].ToInt();
		}
		if(enemyUFO.hasKey("texture"))
		{
			filepath = enemyUFO["texture"].ToString();
		}
	}

	inputStream.close();
}
Enemy* EnemyUFO::Clone() const
{
	return new EnemyUFO(*this);
}


