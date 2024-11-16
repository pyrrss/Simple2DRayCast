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

            dir.push_back(std::cos(angle * M_PI / 180));
            dir.push_back(std::sin(angle * M_PI / 180));
        }   

        void render(SDL_Renderer *renderer, const int MAX_DISTANCE_VIEW, std::vector<float> closestIntersectPoint){

            int endX;
            int endY;

            if(!closestIntersectPoint.empty()){
                
                endX = closestIntersectPoint[0];
                endY = closestIntersectPoint[1];    

            } else {
                
                endX = pos[0] + dir[0] * MAX_DISTANCE_VIEW;
                endY = pos[1] + dir[1] * MAX_DISTANCE_VIEW;    
            }

            float distance = std::sqrt((endX - pos[0]) * (endX - pos[0]) + (endY - pos[1]) * (endY - pos[1]));
            float alpha = 255 * distance / MAX_DISTANCE_VIEW;

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, alpha);
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



