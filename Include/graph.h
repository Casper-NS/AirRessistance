#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_main.h>

float map(float x, float in_min, float in_max, float out_min, float out_max);

void CreateGraph(SDL_Renderer *renderer, int &graph_width, int &graph_height, int &window_width, int &window_height);