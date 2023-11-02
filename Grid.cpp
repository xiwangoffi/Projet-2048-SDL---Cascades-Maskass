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

void Grid::SetCell(int x, int y, int value) {
	Cell* cell = GetCell(x, y);
	SetCell(cell, value);
}

void Grid::SetCell(Cell* cell, int value) {
	cell->Value = value;
}

void Grid::Init() {
	grid.resize(size);

	for (int x = 0; x < size; x++)
	{
		grid[x].resize(size);
		for (int y = 0; y < size; y++)
		{
			Vector2i relative(x, y);
			grid[x][y] = new Cell(relative, 0);
			grid[x][y]->SetAnchors(Vector2(0, 0));
		}
	}

	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			emptyCells.push_back(GetCell(x, y));
		}
	}

	SpawnFreshTiles(2);
}

void Grid::SpawnFreshTiles(int n) {
	for (int i = 0; i < n; i++)
	{
		cout << "aled patron";
		if (emptyCells.size() <= 0) return;

		Cell* cell = GetRandomEmptyCell();
		int value = GetRandomTileValue();

		SetCell(cell, value);
		emptyCells.remove(cell);
	}
}

Cell* Grid::GetRandomEmptyCell() {
	int cellIndex = rand() % emptyCells.size();
	list<Cell*>::iterator it = emptyCells.begin();
	advance(it, cellIndex);
	Cell* out = *it;
	emptyCells.remove(out);
	return out;
}

int Grid::GetRandomTileValue() {
	return rand() % 10 == 0 ? 4 : 2;
};

void Grid::ShiftTilesTowards(Vector2i shiftDir) {
	BatchResetCells();
	for (int x = 0; x < Helpers::GRID_SIZE; x++)
	{
		for (int y = 0; y < Helpers::GRID_SIZE; y++)
		{
			MoveCell(x, y, shiftDir);
		}
	}

	// IF Cells shifted ?
	// SPAWN FRESH TILE
	SpawnFreshTiles(1);
	// WIN COND
	// LOOSE COND
}

bool Grid::CellHasNeighbour(Cell* cell, Vector2i shiftDir) {
	if (shiftDir.x == 1) {
		return cell->RelativePosition.x < (Helpers::GRID_SIZE-1);
	}
	else if (shiftDir.x == -1) {
		return cell->RelativePosition.x > 0;
	}
	else if (shiftDir.y == 1) {
		return cell->RelativePosition.y < (Helpers::GRID_SIZE - 1);
	}
	else if (shiftDir.y == -1) {
		return cell->RelativePosition.y > 0;
	}
	return false;
}

void Grid::MoveCell(int x, int y, Vector2i shiftDir) {
	Cell* cell = GetCell(x, y);
	if (cell->Value == 0) return;

	while (CellHasNeighbour(cell, shiftDir)) {
		Cell* neighbour;
		bool shouldContinue = HandleMovement(cell, neighbour, shiftDir);
		if (shouldContinue) continue;

		bool hasMerged = *cell + *neighbour;
		if (!hasMerged)
			break;

		emptyCells.push_back(neighbour);
		cell->SetHasMerged(true);
		neighbour->SetHasMerged(true);
		continue;
	}
}

bool Grid::HandleMovement(Cell* cell, Cell*& neighbour, Vector2i shiftDir) {
	neighbour = GetCell(cell->RelativePosition + shiftDir);

	if (neighbour->Value == 0) {
		Cell* tmp = grid[cell->Position().x][cell->Position().y];
		grid[cell->Position().x][cell->Position().y] = grid[neighbour->Position().x][neighbour->Position().y];
		grid[neighbour->Position().x][neighbour->Position().y] = tmp;
		cell->RelativePosition += shiftDir;
		neighbour->RelativePosition -= shiftDir;
		return true;
	}

	return false;
}

void Grid::BatchResetCells() {
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			Cell* cell = GetCell(x, y);
			cell->SetHasMerged(false);
		}
	}
}

void Grid::Render(SDL_Renderer* renderer) {
	for (int x = 0; x < Helpers::GRID_SIZE; x++)
	{
		for (int y = 0; y < Helpers::GRID_SIZE; y++)
		{
			Cell* cell = GetCell(x, y);
			cell->Render(renderer);
		}
	}
}