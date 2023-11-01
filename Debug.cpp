#include "Debug.h"

namespace Debug {
	void DisplayFPS(SDL_Renderer* renderer, int fps) {
		if (!DEBUGGING) return;

		string fpsText = "Current FPS: " + to_string(fps);
		
		FPS_Surface = TTF_RenderText_Solid(Fonts::RobotoRegular, fpsText.c_str(), FPS_Color);
		FPS_Texture = SDL_CreateTextureFromSurface(renderer, FPS_Surface);
		
		FPS_Rect.w = FPS_Surface->w;
		FPS_Rect.h = FPS_Surface->h;

		SDL_FreeSurface(FPS_Surface);
		SDL_RenderCopy(renderer, FPS_Texture, NULL, &FPS_Rect);
	}

	void Clean() {
		SDL_DestroyTexture(FPS_Texture);
	}
}