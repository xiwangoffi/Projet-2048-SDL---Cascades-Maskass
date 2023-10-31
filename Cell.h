#pragma once

#include <vector>

using namespace std;

class Cell {
private:
	bool hasMerged;

public:
	int Value;

	Cell(int value = 0);
	~Cell();

	void SetHasMerged(bool value) { hasMerged = value; }

	bool operator+(Cell& cellToMerge);
};