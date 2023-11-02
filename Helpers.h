#pragma once

#include "SDL.h"
#include "Vector2.h"
#include <math.h>

using namespace std;

namespace Helpers {
	const int GRID_SIZE = 4;
	const int MAP_PSIZE = 600;
	const int CELL_PSIZE = 140;
	const int CELL_PMARGIN = 20;
	const int TILE_PSIZE = 120;
	const int TILE_PMARGIN = 10;
	extern Vector2 ORIGIN;

	float Lerp(float a, float b, float t);

	SDL_Color Lerp(const SDL_Color& a, const SDL_Color& b, float t);

	Vector2 Lerp(const Vector2& a, const Vector2& b, float t);
}

namespace Easing {
	float BounceOut(float t);
	float BackOut(float t);
	float BackIn(float t);
	float ElasticInOut(float t);
}