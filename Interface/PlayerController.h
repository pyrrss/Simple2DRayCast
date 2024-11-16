//
// Created by pyrr on 17-09-24.
//

#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "Player.h"


class PlayerController {
    Player *player;
    public:
        PlayerController(Player *player);
        void handleInput(float deltaTime);
        void render(SDL_Renderer* renderer);

};



#endif //PLAYERCONTROLLER_H
