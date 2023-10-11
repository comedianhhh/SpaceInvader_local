#include "Render.h"
#include "GameObject.h"

Render::Render(SDL_Renderer* renderer) : renderer(renderer) {
}

Render::~Render() {
}

void Render::renderGameObject(GameObject& gameObject) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_RenderClear(renderer);

    gameObject.render();

    SDL_RenderPresent(renderer);
}