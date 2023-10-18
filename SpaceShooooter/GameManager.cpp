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

	//save enemies and asteroid
	json::JSON enemies = json::JSON::Array();

	for (int i = 0; i < state.enemies.size(); i++)
	{
		json::JSON enemy;
		enemy["Enemy"]["Rect"]["x"] = state.enemies[i]->GetPosition().x;
		enemy["Enemy"]["Rect"]["y"] = state.enemies[i]->GetPosition().y;
		enemies.append(enemy);
	}
	

	std::ofstream save("save.json");
	save<<document.dump();
	save<<enemies.dump();


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
}