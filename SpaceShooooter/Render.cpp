#include "Render.h"
#include "GameObject.h"

Render::Render(SDL_Renderer* renderer) : renderer(renderer) {
	IMG_Init(IMG_INIT_PNG);
}

Render::~Render() {
	IMG_Quit();
}
SDL_Texture* Render::loadTexture(const char* filepath) {
	SDL_Surface* surface = IMG_Load(filepath);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	return texture;
}
void Render::renderTexture(SDL_Texture* texture, int x, int y) {
	SDL_Rect destination = { x, y, 0, 0 }; 
	SDL_QueryTexture(texture, NULL, NULL, &destination.w, &destination.h);
	SDL_RenderCopy(renderer, texture, NULL, &destination);
}