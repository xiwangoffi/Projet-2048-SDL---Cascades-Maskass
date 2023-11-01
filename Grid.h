#pragma once

#include <iostream>
#include <vector>
#include <list>
#include "Cell.h"

class Grid {
private:
	vector<vector<Cell*>> grid;
	list<Cell*> emptyCells;
	int size;

public:
	Grid(int _size);
	~Grid();

	int GetSize() { return size; }
	Cell* GetCell(int x, int y) { return grid[x][y]; }
	int GetRandomTileValue();

	void SetCell(int x, int y, int value);
	void SetCell(Cell* cell, int value);

	void Init();
};