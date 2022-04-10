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

    //SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
    SDL_RenderSetLogicalSize(renderer, window_width, window_height);

    float graph_width = 32;
    float graph_height = 18; //round(graph_width*window_height/window_width);

    while (!done) {
        while (SDL_PollEvent(&events)) {
            if (events.type == SDL_QUIT) {
                done = true;
                exit(0);
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        
        //SDL_GetWindowSize(sdlWindow, &window_width, &window_height);
        CreateGraph(renderer, graph_width, graph_height, window_width, window_height);
        
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        auto OldX = window_width/4;
        auto OldY = window_height-window_height/8-map(graph_height-5, 0, graph_height, window_height-window_height/8, 0);

        for (float x = 0; x < graph_width; x+=0.01f)
        {
            auto NewX = map(x, 0, graph_width, window_width/4, window_width);
            auto NewY = map(sin(x), 0, graph_height, window_height-window_height/8, 0)-map(graph_height-5, 0, graph_height, window_height-window_height/8, 0);
            SDL_RenderDrawLine(renderer, OldX, OldY, NewX, NewY);
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

