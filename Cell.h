#pragma once

#include "App.h"
#include "Vector2.h"
#include <vector>

using namespace std;

class Cell : public GameObject {
protected:
	bool hasMerged;

public:
	int Value;

	Cell(Vector2 position, int value = 0);
	~Cell();

	virtual void Update(float dT) override;
	virtual void Render(SDL_Renderer* renderer) override;

	void SetHasMerged(bool value) { hasMerged = value; }
	bool operator+(Cell& cellToMerge);
};