#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H

#include "GameObject.h"

class PlayerShip : public GameObject {
public:
    PlayerShip(SDL_Renderer* renderer, int x, int y);
    void update() override;
    void render() override;
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void stopMovingUp();
    void stopMovingDown();
    void stopMovingLeft();
    void stopMovingRight();
    void shoot();

private:

};

#endif // PLAYERSHIP_H
