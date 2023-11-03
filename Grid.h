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
	bool won;
	bool lost;

public:
	Grid(int _size);
	~Grid();

	int GetSize() { return size; }
	bool HasLost() { return lost; }
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

	bool WinCondition();
	bool IsAvailableMoveToward(Vector2i dir);
	bool LooseCondition();

	void Update(float dT);
	void Render(SDL_Renderer* renderer);
};