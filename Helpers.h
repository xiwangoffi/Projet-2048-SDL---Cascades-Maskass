#pragma once

#include "SDL.h"

namespace Helpers {
	static float Lerp(float a, float b, float t) {
		return (a + (b - a) * t);
	}

	static SDL_Color Lerp(SDL_Color a, SDL_Color b, float t) {
		SDL_Color out = {
			a.r + (b.r - a.r) * t,
			a.g + (b.g - a.g) * t,
			a.b + (b.b - a.b) * t
		};
		return out;
	}
}