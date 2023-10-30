#pragma once

#include "SDL.h"

namespace Helpers {
	static float Lerp(float a, float b, float t) {
		return (a + (b - a) * t);
	}

	static float EaseIn(float t) {
		return t * t;
	}

	static float EaseOutBack(float t) {
		const float c1 = 1.70158f;
		const float c3 = c1 + 1;
		return 1 + c3 * pow(t - 1, 3) + c1 * pow(t - 1, 2);
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