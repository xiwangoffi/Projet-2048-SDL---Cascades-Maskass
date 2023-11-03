#include "Helpers.h"

namespace Helpers {
	Vector2 ORIGIN = Vector2::zero();

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

namespace Easing {
	float QuadOut(float t) {
		return 1 - (1 - t) * (1 - t);
	}

	float BounceOut(float t) {
		const float n1 = 7.5625;
		const float d1 = 2.75;

		if (t < 1 / d1) {
			return n1 * t * t;
		}
		else if (t < 2 / d1) {
			return n1 * (t -= 1.5 / d1) * t + 0.75;
		}
		else if (t < 2.5 / d1) {
			return n1 * (t -= 2.25 / d1) * t + 0.9375;
		}
		else {
			return n1 * (t -= 2.625 / d1) * t + 0.984375;
		}
	}

	float BackOut(float t) {
		const float c1 = 1.70158;
		const float c3 = c1 + 1;

		return 1 + c3 * pow(t - 1, 3) + c1 * pow(t - 1, 2);
	}

	float BackIn(float t) {
		const float c1 = 1.70158;
		const float c3 = c1 + 1;

		return c3 * t * t * t - c1 * t * t;
	}

	float ElasticInOut(float t) {
		const float c5 = (2 * M_PI) / 4.5;

		return t == 0
			? 0 : 
			t == 1
			? 1
			: t < 0.5
			? -(pow(2, 20 * t - 10) * sin((20 * t - 11.125) * c5)) / 2
			: (pow(2, -20 * t + 10) * sin((20 * t - 11.125) * c5)) / 2 + 1;
	}
}