#pragma once
#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_
#include <SDL.h>
#include <vector>
#include <SDL_image.h>
class BackGround
{
public:
    BackGround(SDL_Renderer* renderer);
    ~BackGround();

    void Render();
    void AddStar();
    void AddCloud();
    void MoveObjects();

private:
    SDL_Renderer* renderer;
    SDL_Texture* bgTexture;
    SDL_Rect position;
    int scrollSpeed;
    int MaxStars;
    int MaxClouds;
    std::vector<SDL_Rect> bigStars;
    std::vector<SDL_Rect> smallStars;
    std::vector<SDL_Rect> clouds;
    SDL_Texture* bigStarTexture;
    SDL_Texture* smallStarTexture;
    SDL_Texture* cloudTexture;

};
#endif // !_BACKGROUND_H_

