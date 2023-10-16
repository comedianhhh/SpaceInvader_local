#include "BackGround.h"

#include <iostream>
BackGround::BackGround(SDL_Renderer* renderer) {
    this->renderer = renderer;
    bgTexture = IMG_LoadTexture(renderer, "Asset/Background/starBackground.png");
    position = { 0, 0,800,600 };
    scrollSpeed = 1;
    MaxStars = 10;
    MaxClouds = 5;
    bigStarTexture = IMG_LoadTexture(renderer, "Asset/Background/starBig.png");
    smallStarTexture = IMG_LoadTexture(renderer, "Asset/Background/starSmall.png");
    cloudTexture= IMG_LoadTexture(renderer, "Asset/Background/nebula.png");

}

BackGround::~BackGround() {
    SDL_DestroyTexture(bgTexture);
    SDL_DestroyTexture(bigStarTexture);
    SDL_DestroyTexture(smallStarTexture);
    SDL_DestroyTexture(cloudTexture);

}



void BackGround::Render() {

    SDL_RenderCopy(renderer, bgTexture, nullptr, &position);

    for (const auto& star : bigStars) {
        SDL_RenderCopy(renderer, bigStarTexture, nullptr, &star);
    }

    // Render small stars
    for (const auto& star : smallStars) {
        SDL_RenderCopy(renderer, smallStarTexture, nullptr, &star);
    }

    // Render clouds
    for (const auto& cloud : clouds) {
        SDL_RenderCopy(renderer, cloudTexture, nullptr, &cloud);
    }
}

void BackGround::AddStar() {
    if (bigStars.size() >= MaxStars)
    {
		return;
	}
    int x = rand() % 800;
    int y = rand() % 600;

    if (rand() % 2 == 0) {
        bigStars.push_back({ x, y, 10, 10 });
    }
    else {
        smallStars.push_back({ x, y, 5, 5 });
    }
}
void BackGround::AddCloud() 
{
    if (clouds.size() >= MaxClouds)
    {
		return;
	}
	int x = rand() % 800;
	int y = rand() % 600;

	clouds.push_back({ x, y, 100, 70 });
}
void BackGround::MoveObjects() {
    // Move clouds
    for (auto& cloud : clouds) {
        cloud.y += scrollSpeed;  // Adjust the speed as needed
        cloud.x += scrollSpeed;
        if (cloud.y > 600) {
            // If the cloud is below the screen, reset its position above
            cloud.y = -cloud.h;
            cloud.x = rand() % 800;
        }
    }
}