#pragma once

#include "SDL.h"
#include "Vector2.h"

using namespace std;

namespace Helpers {
	float Lerp(float a, float b, float t);

	SDL_Color Lerp(const SDL_Color& a, const SDL_Color& b, float t);

	Vector2 Lerp(const Vector2& a, const Vector2& b, float t);
}