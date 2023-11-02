#pragma once

#include <vector>
#include "Vector2.h"
#include "GameObject.h"
#include "Resources.h"

using namespace std;

class Cell : public GameObject {
protected:
	bool hasMerged;

public:
	int Value;
	Vector2i RelativePosition;

	Cell(Vector2i _position, int value = 0);
	~Cell();

	void Update(float dT) override;
	void Render(SDL_Renderer* renderer) override;

	void SetHasMerged(bool value) { hasMerged = value; }
	bool operator+(Cell& cellToMerge);
};