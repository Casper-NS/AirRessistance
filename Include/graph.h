#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_main.h>
#include <math.h>

float map(float x, float in_min, float in_max, float out_min, float out_max);

void CreateGraph(SDL_Renderer *renderer, float &graph_width, float &graph_height, int &window_width, int &window_height);