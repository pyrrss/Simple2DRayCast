#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include "obstacle.cpp"
#include <cmath>

class Ray{
    public:
        std::vector<float> pos;
        std::vector<double> dir;
        Ray(std::vector<float> pos, int angle){
            
            this->pos = pos;

            float radians = angle * M_PI / 180;

            dir.push_back(std::cos(radians));
            dir.push_back(std::sin(radians));
        }   

        void render(SDL_Renderer *renderer){

            int endX = pos[0] + dir[0] * 10;
            int endY = pos[1] + dir[1] * 10;


            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawLine(renderer, pos[0], pos[1], endX, endY);

        }

        std::vector<float> cast(Obstacle wall){
            std::vector<float> intersectPoint;

            float x1 = wall.startPoint[0];
            float y1 = wall.startPoint[1];
            float x2 = wall.endPoint[0];
            float y2 = wall.endPoint[1];

            float x3 = pos[0];
            float y3 = pos[1];
            float x4 = pos[0] + dir[0];
            float y4 = pos[1] + dir[1];
        
            float denominator = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
            
            if(denominator == 0)
            {
                return {};
            }

            float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / denominator;
            float u = -1 * ((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / denominator;
        
            if(t >= 0 && t <= 1 && u >= 0)
            {
                intersectPoint.push_back(x1 + (t * (x2 - x1)));
                intersectPoint.push_back(y1 + (t * (y2 - y1)));
                return intersectPoint;
            } else{
                return {};
            }

        }





};



