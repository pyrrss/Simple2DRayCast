#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <cmath>

#include "ray.cpp"

class Player{
    public:
        std::vector<float> pos;
        std::vector<Ray> rays;

        Player(std::vector<float> pos){
            this->pos = pos;
            
            for(int i = 0;i < 360;i++)
            {
                Ray ray = Ray(pos, i);
                rays.push_back(ray);
            }
        

        }

        void setPos(float x, float y){
            pos[0] = x;
            pos[1] = y;

            for(Ray &ray : rays)
            {
                ray.pos[0] = pos[0];
                ray.pos[1] = pos[1];
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
                    if(intersectPoint.size() > 0)
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

                if(!closestIntersectPoint.empty())
                {
                    SDL_RenderDrawLine(renderer, pos[0], pos[1], closestIntersectPoint[0], closestIntersectPoint[1]);
                }
            }
            
           

        }

        void render(SDL_Renderer *renderer){

            for(Ray ray : rays)
            {
                ray.render(renderer);

            }

        }




};