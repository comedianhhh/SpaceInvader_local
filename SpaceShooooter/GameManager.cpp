#include "GameManager.h"
#include <fstream>
#include"json.hpp"
#include <iostream>

GameManager::GameManager() {}

GameManager::~GameManager() {}

void GameManager::SaveGame(const GameState& state)
{

	json::JSON document;
	document["PlayerShip"]["lives"] = state.playerShip->GetLives();
	document["PlayerShip"]["score"] = state.playerShip->GetScore();
	document["PlayerShip"]["Rect"]["x"] = state.playerShip->GetPosition().x;
	document["PlayerShip"]["Rect"]["y"] = state.playerShip->GetPosition().y;

	json::JSON asteroids = json::JSON::Array();
	for (int i = 0; i < state.asteroids.size();i++)
	{
		json::JSON asteroid;
		asteroid["Asteroid"]["Rect"]["x"] = state.asteroids[i]->GetX();
		asteroid["Asteroid"]["Rect"]["y"] = state.asteroids[i]->GetY();
		asteroid["Asteroid"]["Size"] = state.asteroids[i]->GetSize();
		asteroids.append(asteroid);
	}
	//save enemies and asteroid
	document["Asteroids"] = asteroids;
	json::JSON enemies = json::JSON::Array();

	for (int i = 0; i < state.enemies.size(); i++)
	{
		json::JSON enemy;
		enemy["Enemy"]["Type"] = state.enemies[i]->GetType();
		enemy["Enemy"]["Rect"]["x"] = state.enemies[i]->GetPosition().x;
		enemy["Enemy"]["Rect"]["y"] = state.enemies[i]->GetPosition().y;
		enemies.append(enemy);
	}
	document["Enemies"] = enemies;
	std::ofstream save("save.json");
	save << document.dump();
}

void GameManager::LoadGame(GameState& state)
{
	std::ifstream save("save.json");
	std::string str((std::istreambuf_iterator<char>(save)), std::istreambuf_iterator<char>());
	json::JSON document = json::JSON::Load(str);

	if (document.hasKey("PlayerShip"))
	{
		json::JSON playerShip = document["PlayerShip"];
		
		if (playerShip.hasKey("lives"))
		{
			state.playerShip->SetLives(playerShip["lives"].ToInt());
		}
		if (playerShip.hasKey("score"))
		{
			state.playerShip->SetScore(playerShip["score"].ToInt());
		}
		if (playerShip.hasKey("Rect"))
		{
			state.playerShip->SetX(playerShip["Rect"]["x"].ToInt());
			state.playerShip->SetY(playerShip["Rect"]["y"].ToInt());
		}
	}
	if (document.hasKey("Enemies"))
	{
		state.enemies.clear();
		for (auto& enemy : document["Enemies"].ArrayRange())
		{
			if (enemy["Enemy"].hasKey("Type") && enemy["Enemy"]["Type"].ToString() == "Ship")
			{
				EnemyShip* newE = new EnemyShip({ 0, 0, 50, 50 }, 5, 10);
				newE->LoadData();
				newE->SetX(enemy["Enemy"]["Rect"]["x"].ToInt());
				newE->SetY(enemy["Enemy"]["Rect"]["y"].ToInt());
				state.enemies.push_back(newE);
			}
			else if (enemy["Enemy"].hasKey("Type") && enemy["Enemy"]["Type"].ToString() == "UFO")
			{
				EnemyUFO* newU = new EnemyUFO({ 0, 0, 50, 50 }, 3, 10);
				newU->LoadData();
				newU->SetX(enemy["Enemy"]["Rect"]["x"].ToInt());
				newU->SetY(enemy["Enemy"]["Rect"]["y"].ToInt());
				state.enemies.push_back(newU);
			}
		}


	}
	if (document.hasKey("Asteroids"))
	{
	
		state.asteroids.clear();
		for (auto& asteroid : document["Asteroids"].ArrayRange())
		{
			Asteroid* newA = new Asteroid( 0,0, 30);
			newA->SetX(asteroid["Asteroid"]["Rect"]["x"].ToInt());
			newA->SetY(asteroid["Asteroid"]["Rect"]["y"].ToInt());
			newA->SetSize(asteroid["Asteroid"]["Size"].ToInt());
			state.asteroids.push_back(newA);
		}
	}
	
}
void GameManager::ClearEnemies(std::vector<Enemy*>& enemies)
{
 	for(auto& enemy : enemies)
	{
		delete enemy;
		enemy = nullptr;
	}
	enemies.clear();
}
void GameManager::ClearAsteroids(std::vector<Asteroid*>& asteroids)
{
	for (auto& asteroid : asteroids)
	{
		delete asteroid;
		asteroid = nullptr;
	}
	asteroids.clear();
}