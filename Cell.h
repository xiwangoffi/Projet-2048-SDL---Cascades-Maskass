#pragma once

#include <vector>
#include "Vector2.h"
#include "GameObject.h"
#include "Resources.h"

using namespace std;

class Cell : public GameObject {
protected:
	bool hasMerged;
	float animationTime;
	float animationDuration;
	Vector2 startPosition;
	Vector2 targetPosition;
	Vector2 startSize;
	Vector2 targetSize;

public:
	int Value;
	Vector2i RelativePosition;

	Cell(Vector2i _position, int value = 0);
	~Cell();

	void SetRelativePosition(Vector2i _position);
	void CalculatePositionFromRelativePos();

	void Update(float dT) override;
	void Render(SDL_Renderer* renderer) override;

	void AnimatePosition(float duration);
	void AnimateSize(float duration, Vector2 startSize);

	void SetHasMerged(bool value) { hasMerged = value; }
	bool operator+(Cell& cellToMerge);
};