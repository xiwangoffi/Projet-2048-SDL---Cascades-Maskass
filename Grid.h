#pragma once

#include <iostream>
#include <vector>
#include <list>
#include "Cell.h"

class Grid {
private:
	std::vector<std::vector<Cell*>> grid;
	std::list<Cell*> emptyCells;
	int size;

public:
	Grid(int _size);
	~Grid();

	int GetSize() { return size; }
	Cell* GetCell(int x, int y) { return grid[x][y]; }
	Cell* GetCell(Vector2i position) { return grid[position.x][position.y]; }
	Cell* GetRandomEmptyCell();
	int GetRandomTileValue();

	void SetCell(int x, int y, int value);
	void SetCell(Cell* cell, int value);

	void Init();

	void SpawnFreshTiles(int n);
	void ShiftTilesTowards(Vector2i shiftDir);
	void MoveCell(int x, int y, Vector2i shiftDir);
	bool HandleMovement(Cell* cell, Cell*& neighbour, Vector2i shiftDir);
	void BatchResetCells();
	bool CellHasNeighbour(Cell* cell, Vector2i shiftDir);

	void Render(SDL_Renderer* renderer);
};