#include <iostream>
#include <SDL2/SDL.h>
#include <ctime>

#include "obstacle.cpp"

#include "player.cpp"

#define WIDTH 1280
#define HEIGHT 720


int main(){
    SDL_Window *window;
    SDL_Renderer *renderer;
    
    std::srand(std::time(NULL));

    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "Error starting SDL2" << "\n";
        exit(1);
    }

    window = SDL_CreateWindow("Simple2DRayCast", 0, 0, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);



    bool isRunning = true;
    Player player = Player({WIDTH / 2, HEIGHT / 2});
    
    std::vector<Obstacle> walls;
    for(int i = 0;i < 5;i++)
    {   
        Obstacle wall = Obstacle(rand()%1280, rand()%720, rand()%1280, rand()%720);
        walls.push_back(wall);
    }

    float mouseX, mouseY;
    while(isRunning)
    {

        SDL_Event event;
        while(SDL_PollEvent( &event ))
        {
            if(event.type == SDL_QUIT)
            {
                isRunning = false;
            }

            if(event.type == SDL_MOUSEMOTION)
            {
                mouseX = event.motion.x;
                mouseY = event.motion.y;
            }
        }

        SDL_SetRenderDrawColor(renderer, 154, 15, 162, 255);
        SDL_RenderClear(renderer);
        
        for(Obstacle wall : walls)
        {
            wall.render(renderer);
        }
        player.render(renderer);
        player.setPos(mouseX, mouseY);
        player.lookWalls(walls, renderer);
        
        




        SDL_RenderPresent(renderer);
    }








    return 0;
}