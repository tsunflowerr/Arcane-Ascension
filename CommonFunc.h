#pragma once
#ifndef COMMON_FUNCTION_H_ 
#define COMMON_FUNCTION_H_ 

#include <Windows.h>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "BaseObject.h"


static SDL_Window* g_window = NULL; 
static SDL_Renderer* g_screen = NULL; 
static SDL_Event g_event; 
static SDL_Surface* g_image_menu = NULL;

const int SCREEN_WIDTH = 1280; 
const int SCREEN_HEIGHT = 640; 
const int SCREEN_BPP = 32; 

const int COLOR_KEY_R = 167; 
const int COLOR_KEY_G = 175; 
const int COLOR_KEY_B = 180; 

const int RENDER_DRAW_COLOR = 255; 

const int FPS = 70;

 

#define BLANK_TILE 0 
#define TILE_SIZE 64 

#define MAX_MAP_X 400 
#define MAX_MAP_Y 10

#define STATE_MONEY 4 

#define LUCKKY_BOX 7

typedef struct Input
{
	int left_; 
	int right_; 
	int up_; 
	int down_; 
	int jump_; 
};

typedef struct Map
{
	int start_x_;
	int start_y_;

	int max_x_;
	int max_y_;

	int tile[MAX_MAP_Y][MAX_MAP_X];
	char* file_name_;
};

namespace SDLCommonFunc
{
	bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2); 
}

#endif