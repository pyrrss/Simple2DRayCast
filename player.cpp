#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <cmath>

#include "ray.cpp"

class Player{
    public:
        std::vector<float> pos;
        std::vector<Ray> rays;
        const int PLAYER_VEL = 100;
        float direction = 0;
        const int MAX_DISTANCE_VIEW = 400;

        Player(std::vector<float> pos){
            this->pos = pos;
            
            for(int i = -22;i < 22;i++)
            {
                Ray ray = Ray(pos, direction + i);
                rays.push_back(ray);
            }

        }

        void lookWalls(std::vector<Obstacle> walls, SDL_Renderer *renderer){
            
            
            for(Ray ray : rays)
            {
                float minDistance = 1280;
                std::vector<float> closestIntersectPoint;
            
                for(Obstacle wall : walls)
                {

                    std::vector<float> intersectPoint = ray.cast(wall);
                    if(!intersectPoint.empty())
                    {   
                        float x1 = ray.pos[0];
                        float y1 = ray.pos[1];
                        float x2 = intersectPoint[0];
                        float y2 = intersectPoint[1];
                        float dist = std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

                        if(dist < minDistance)
                        {
                            minDistance = dist;
                            closestIntersectPoint = intersectPoint;
                        }

                    }
                
                }

                if(!closestIntersectPoint.empty() && minDistance <= MAX_DISTANCE_VIEW)
                {
                    ray.render(renderer, MAX_DISTANCE_VIEW, closestIntersectPoint);
                } else{
                    ray.render(renderer, MAX_DISTANCE_VIEW, {});
                }

            }
            
           

        }

        void setKeyPos(float deltaTime){
            
            const Uint8* keystate = SDL_GetKeyboardState(NULL);

            if (keystate[SDL_SCANCODE_A])
            {
                // pos[0] -= PLAYER_VEL * deltaTime;
                direction -= 0.05;
            }

            if (keystate[SDL_SCANCODE_D])
            {
                // pos[0] += PLAYER_VEL * deltaTime;
                direction += 0.05;
            }

            if (keystate[SDL_SCANCODE_W]) 
            {

                pos[0] += PLAYER_VEL * deltaTime * std::cos(direction * M_PI / 180.0);
                pos[1] += PLAYER_VEL * deltaTime * std::sin(direction * M_PI / 180.0);
            
            }

            if (keystate[SDL_SCANCODE_S]) 
            {
            
                pos[0] -= PLAYER_VEL * deltaTime * std::cos(direction * M_PI / 180.0);
                pos[1] -= PLAYER_VEL * deltaTime * std::sin(direction * M_PI / 180.0);
            
            }

            for(int i = 0;i < rays.size();i++) {
                
                rays[i].pos[0] = pos[0];
                rays[i].pos[1] = pos[1];
                rays[i].dir = {std::cos((direction + i - 22) * M_PI / 180.0), 
                               std::sin((direction + i - 22) * M_PI / 180.0)};
            }

        }




};