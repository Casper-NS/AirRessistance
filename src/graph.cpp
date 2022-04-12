#include "graph.h"

    float graph_width;
    float graph_height;
    SDL_Renderer *renderer;
    SDL_Window *sdlWindow;
    int window_width;
    int window_height;
    enum Position {
        center,
        bottom_right,
        top_right
    };

XYPlane::XYPlane(SDL_Renderer *renderer, SDL_Window *window, float width, float height) 
    {
        graph_width = width;
        graph_height = height;
        this->renderer = renderer;
        sdlWindow = window;
        SDL_GetWindowSize(sdlWindow, &window_width, &window_height);
    }

XYPlane::XYPlane() = default;

void XYPlane::draw(SDL_Renderer *renderer, Position position, int OffsetX, int OffsetY) 
    {  
        int origin_offset_x = window_width/2;
        int origin_offset_y = window_height/2;
        
        switch (position) {
            case center:
            //This one is a little fucked right now, some issues with the background
                RenderBG(renderer, 0, 0, window_width, window_width);
                SDL_SetRenderDrawColor(renderer, 150, 80, 80, 200);
                SDL_RenderDrawLine(renderer, 0, origin_offset_y-OffsetY, window_width, origin_offset_y-OffsetY);
                SDL_RenderDrawLine(renderer, origin_offset_x+OffsetX, window_height, origin_offset_x+OffsetX, 0);
                break;
            case top_right:
                RenderBG(renderer, origin_offset_x+OffsetX, origin_offset_y-OffsetY, window_width, 0);
                SDL_SetRenderDrawColor(renderer, 150, 80, 80, 200);
                SDL_RenderDrawLine(renderer, origin_offset_x+OffsetX, origin_offset_y-OffsetY, window_width, origin_offset_y-OffsetY);
                SDL_RenderDrawLine(renderer, origin_offset_x+OffsetX, origin_offset_y-OffsetY, origin_offset_x+OffsetX, 0);
                break;
            case bottom_right:
                RenderBG(renderer, origin_offset_x+OffsetX, origin_offset_y-OffsetY, window_width, window_height);
                SDL_SetRenderDrawColor(renderer, 150, 80, 80, 200);
                SDL_RenderDrawLine(renderer, origin_offset_x+OffsetX, origin_offset_y-OffsetY, window_width, origin_offset_y-OffsetY);
                SDL_RenderDrawLine(renderer, origin_offset_x+OffsetX, origin_offset_y-OffsetY, origin_offset_x+OffsetX, window_height);
                break;
        }

    }

void XYPlane::RenderBG(SDL_Renderer *renderer, int originX, int originY, int width, int height)
    {
        graph_width = graph_height*window_width/window_height;

        SDL_SetRenderDrawColor(renderer, 30, 30, 50, 50);

        for (int x = 0; x < graph_width; ++x)
        {
        SDL_RenderDrawLine(renderer, 
                            map(x, 0, graph_width, originX, window_width), 
                            map(0, 0, graph_height, originY, height), 
                            map(x, 0, graph_width, originX, window_width), 
                            map(graph_height, 0, graph_height, originY, height));
        }

        for (int y = 0; y < graph_height; ++y)
        {
        SDL_RenderDrawLine(renderer, 
                            map(0, 0, graph_width, originX, window_width), 
                            map(y, 0, graph_height, originY, height), 
                            map(window_width, 0, graph_width, originX, window_width), 
                            map(y, 0, graph_height, originY, height));
        }
    }

//Maps the size given with in_min and in_max to the windows size and returns the relative cordinate;
float XYPlane::map(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


