#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_main.h>
#include <math.h>

class XYPlane {
    private:
    float graph_width;
    float graph_height;
    SDL_Renderer *renderer;
    void RenderBG(SDL_Renderer *renderer, int originX, int originY, int width, int height);

    public:
    enum Position {
        center,
        bottom_right,
        top_right
    };

    XYPlane();
    XYPlane(SDL_Renderer *renderer, SDL_Window *window, float width, float height);
    void draw(SDL_Renderer *renderer, Position position, int OffsetX, int OffsetY);
    float map(float x, float in_min, float in_max, float out_min, float out_max);
    void CreateGraph(SDL_Renderer *renderer, float &graph_width, float &graph_height, int &window_width, int &window_height);
};

