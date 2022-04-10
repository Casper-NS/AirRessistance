#include <sqlite3.h>
#include "graph.h"
#include <stdio.h>



int main(int argc, char **argv) {


    int window_width = 1920;
    int window_height = 1080;
    bool done = false;

    // Initialize SDL and check for error  
    if((SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO)==-1)) { 
        printf("Could not initialize SDL: %s.\n", SDL_GetError());
        exit(-1);
    }

    printf("SDL initialized.\n");

    //Clean up on exit
    atexit(SDL_Quit);

    SDL_Window *sdlWindow = SDL_CreateWindow("SDL2",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              window_width, window_height,
                              SDL_WINDOW_RESIZABLE);
    
    if (sdlWindow == NULL) {
        printf("Unable to create sdl window: %s\n", SDL_GetError());
        exit(-1);
    }
    
    SDL_Event events;

    SDL_Renderer *renderer = SDL_CreateRenderer(sdlWindow, -1, 0);

    if (renderer == NULL) {
        printf("Unable to create renderer: %s\n", SDL_GetError());
        exit(-1);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, window_width, window_height);

    int graph_width = 100;
    int graph_height = 50;


    while (!done) {
        while (SDL_PollEvent(&events)) {
            if (events.type == SDL_QUIT) {
                done = true;
                exit(0);
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        
        CreateGraph(renderer, graph_width, graph_height, window_width, window_height);
        
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        auto OldX = 0;
        auto OldY = 0;

        for (float x = -10; x < 10; x+=0.05f)
        {
            auto NewX = map(x, -10, 10, window_width/4, window_width);
            auto NewY = map(sin(x), -5, 5, 0, window_height);
            SDL_RenderDrawPoint(renderer, NewX, NewY);
            OldX = NewX;
            OldY = NewY;
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / 60);
    }


   /* Shutdown all subsystems */
    SDL_Quit();
    printf("Quiting SDL.\n");

    exit(0);
}

