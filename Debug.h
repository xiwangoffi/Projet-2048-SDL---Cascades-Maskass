#pragma once

#include "SDL.h"
#include <string>
#include "App.h"
#include "Resources.h"
#include "App.h"

namespace Debug {
	static bool DEBUGGING = true;
	static SDL_Surface* FPS_Surface;
	static SDL_Texture* FPS_Texture;
	static SDL_Rect FPS_Rect;
	static SDL_Color FPS_Color = { 0, 0, 0 };

	void DisplayFPS(SDL_Renderer* renderer, int fps);
	void Clean();
}