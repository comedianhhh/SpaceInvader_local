#include "PlayerShip.h"

PlayerShip::PlayerShip(SDL_Rect initialPosition, int live,int shootTimer,int score)
    : position(initialPosition), lives(live),shootTimer(shootTimer),score(score) 
{
    damage = 2;
    filepath = "Asset/Mainplayer/player.png";

}

PlayerShip::~PlayerShip() {}

void PlayerShip::HandleInput(const Uint8* keyboardState, std::vector<Projectile*>& projectiles)
{
    int adjustedSpeed = 1;

    if (keyboardState[SDL_SCANCODE_W]) {
        position.y -= adjustedSpeed;
    }
    if (keyboardState[SDL_SCANCODE_S]) {
        position.y += adjustedSpeed;
    }
    if (keyboardState[SDL_SCANCODE_A]) {
        position.x -= adjustedSpeed;
    }
    if (keyboardState[SDL_SCANCODE_D]) {
        position.x += adjustedSpeed;
    }
    if(keyboardState[SDL_SCANCODE_SPACE]&&shootTimer<=0) {
        projectiles.push_back(Shoot());
        shootTimer = 100;
	}
    if (shootTimer > 0) {
		shootTimer--;
	}
}

void PlayerShip::Update() {
}

void PlayerShip::Render(SDL_Renderer* renderer) 
{

    SDL_Surface* surface = IMG_Load(filepath.c_str());

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface); 

    SDL_RenderCopy(renderer, texture, nullptr, &position);

    SDL_DestroyTexture(texture);
    

}

Projectile* PlayerShip::Shoot() {
    const int projectileXOffset = 20;
    const int projectileYOffset = -10;

    return new Projectile(position.x + projectileXOffset, position.y + projectileYOffset, 1, true);
}

void PlayerShip::AddScore(int amount)
{
	score += amount;
}
void PlayerShip::TakeDamage() {
    lives--;
}

bool PlayerShip::IsDestroyed() const {

    return lives <= 0;
}

void PlayerShip::Reset() {
    lives = 3;
}
SDL_Rect PlayerShip::GetPosition()const
{
	return position;
}
int PlayerShip::GetLives() const
{
	return lives;
}
int PlayerShip::GetScore() const
{
	return score;
}
void PlayerShip::LoadData() 
{
    std::ifstream inputStream("PlayerShip.json");
    std::string str((std::istreambuf_iterator<char>(inputStream)), std::istreambuf_iterator<char>());
    json::JSON document = json::JSON::Load(str);
    if (document.hasKey("PlayerShip"))
    {
        json::JSON playerShip = document["PlayerShip"];
        if (playerShip.hasKey("lives"))
        {
            lives = playerShip["lives"].ToInt();
        }
        if (playerShip.hasKey("damage"))
        {
            damage = playerShip["damage"].ToInt();
        }
        if(playerShip.hasKey("shootTimer"))
		{
			shootTimer = playerShip["shootTimer"].ToInt();
		}
        if (playerShip.hasKey("texture")) 
        {
            filepath = playerShip["texture"].ToString();
            std::cout<< filepath << std::endl;
        }
    }
}