#include "Helpers.h"

namespace Helpers {
	float Lerp(float a, float b, float t) {
		return (a + (b - a) * t);
	}

	SDL_Color Lerp(const SDL_Color& a, const SDL_Color& b, float t) {
		SDL_Color out = {
			a.r + (b.r - a.r) * t,
			a.g + (b.g - a.g) * t,
			a.b + (b.b - a.b) * t
		};
		return out;
	}

	Vector2 Lerp(const Vector2& a, const Vector2& b, float t) {
		return Vector2(
			a.x + (b.x - a.x) * t,
			a.y + (b.y - a.y) * t
		);
	}
}