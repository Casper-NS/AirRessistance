#include "graph.h"

//Maps the size given with in_min and in_max to the windows size and returns the relative cordinate;
float map(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

//Draws the graph in the buffer
void CreateGraph(SDL_Renderer *renderer, int &graph_width, int &graph_height, int &window_width, int &window_height)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 100, 255);

    int offsetX = window_width / 4;
    int offsetY = window_height - window_height/8;

    for (int x = 0; x < graph_width; ++x)
    {
        SDL_RenderDrawLine(renderer, 
                            map(x, 0, graph_width, offsetX, window_width), 
                            map(0, 0, graph_height, offsetY, 0), 
                            map(x, 0, graph_width, offsetX, window_width), 
                            map(graph_height, 0, graph_height, offsetY, 0));
    }
    
    for (int y = 0; y < graph_height; ++y)
    {
        SDL_RenderDrawLine(renderer, 
                            map(0, 0, graph_width, offsetX, window_width), 
                            map(y, 0, graph_height, offsetY, 0), 
                            map(window_width, 0, graph_width, offsetX, window_width), 
                            map(y, 0, graph_height, offsetY, 0));
    }

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawLine(renderer, offsetX, offsetY, window_width, offsetY);
    SDL_RenderDrawLine(renderer, offsetX, offsetY, offsetX, 0);

}