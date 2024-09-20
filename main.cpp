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
    float currentTime;
    float deltaTime;
    float lastTime = 0; 
    while(isRunning)
    {
        currentTime = SDL_GetTicks();
        deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;
    
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

            if(event.type == SDL_KEYDOWN)
            {
                switch(event.key.keysym.sym)
                {
                    case SDLK_m:
                        Obstacle wall = Obstacle(rand()%1280, rand()%720, rand()%1280, rand()%720);
                        walls.push_back(wall);
                        break;
                }
                
            }
            
        }

        SDL_SetRenderDrawColor(renderer, 154, 15, 162, 255);
        SDL_RenderClear(renderer);
        
        for(Obstacle wall : walls)
        {
            wall.render(renderer);
        }

        
        // player.setMousePos(mouseX, mouseY);
        player.lookWalls(walls, renderer);
        player.setKeyPos(deltaTime);
        SDL_RenderPresent(renderer);


    }





    return 0;
}