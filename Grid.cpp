#include "Grid.h"

Grid::Grid(int _size) {
	size = _size;
}

Grid::~Grid()
{
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			delete GetCell(x, y);
		}
	}
}

void Grid::Init() {
	grid.resize(size);

	for (int x = 0; x < size; x++)
	{
		grid[x].resize(size);
		for (int y = 0; y < size; y++)
		{
			grid[x][y] = new Cell(Vector2::zero());
		}
	}

	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			emptyCells.push_back(GetCell(x, y));
		}
	}
}

void Grid::SetCell(int x, int y, int value) {
	Cell* cell = GetCell(x, y);
	SetCell(cell, value);
}

void Grid::SetCell(Cell* cell, int value) {
	cell->Value = value;
}

int Grid::GetRandomTileValue()
{
	return 0;
}