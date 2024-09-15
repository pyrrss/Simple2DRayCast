#ifndef obstacle
#define obstacle

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>


class Obstacle{
    public:
        std::vector<float> startPoint;
        std::vector<float> endPoint;
        Obstacle(float x1, float y1, float x2, float y2){
            
            startPoint.push_back(x1);
            startPoint.push_back(y1);

            endPoint.push_back(x2);
            endPoint.push_back(y2);

            
        }

        void render(SDL_Renderer *renderer){
        
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawLine(renderer, startPoint[0], startPoint[1], endPoint[0], endPoint[1]);
        
        }
};


#endif