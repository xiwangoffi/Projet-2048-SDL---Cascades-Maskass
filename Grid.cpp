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
		if (emptyCells.size() <= 0) return;

		Cell* cell = GetRandomEmptyCell();
		int value = GetRandomTileValue();

		SetCell(cell, value);
		cell->AnimateSize(0.5, Vector2::zero());
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
	if (!IsAvailableMoveToward(shiftDir)) return;
	
	Mix_PlayChannel(-1, Audio::Sand, 0);

	BatchResetCells();
	if (shiftDir.x == -1 || shiftDir.y == -1) {
		for (int x = 0; x < Helpers::GRID_SIZE; x++)
		{
			for (int y = 0; y < Helpers::GRID_SIZE; y++)
			{
				MoveCell(x, y, shiftDir);
			}
		}
	}
	else if (shiftDir.x == 1 || shiftDir.y == 1) {
		for (int x = Helpers::GRID_SIZE-1; x >= 0; x--)
		{
			for (int y = Helpers::GRID_SIZE-1; y >= 0; y--)
			{
				MoveCell(x, y, shiftDir);
			}
		}
	}

	SpawnFreshTiles(1);
	if (WinCondition() && !won) {
		won = true;
		cout << "Well done you won!";
		Mix_VolumeMusic(MIX_MAX_VOLUME / 4);
		Mix_PlayMusic(Audio::Crab, -1);
	}
	else if (LooseCondition() && !lost) {
		lost = true;
		cout << "Oh no you lost!";
		Mix_PlayChannel(-1, Audio::Loose, 0);
	}
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

void PlayRandomBubbleSound() {
	int bubbleIndex = rand() % 3;
	if (Mix_PlayChannel(-1, Audio::Bubbles[bubbleIndex], 0) == -1) {
		printf("Sound cannot be played: %s", Mix_GetError());
	}
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

		PlayRandomBubbleSound();
		emptyCells.push_back(neighbour);
		cell->SetHasMerged(true);
		neighbour->SetHasMerged(true);
		continue;
	}
}

bool Grid::HandleMovement(Cell* cell, Cell*& neighbour, Vector2i shiftDir) {
	int x = cell->RelativePosition.x;
	int y = cell->RelativePosition.y;
	neighbour = GetCell(cell->RelativePosition + shiftDir);

	if (neighbour->Value == 0) {
		Cell* tmp = grid[x][y];
		grid[x][y] = grid[x + shiftDir.x][y + shiftDir.y];
		grid[x + shiftDir.x][y + shiftDir.y] = tmp;

		cell->RelativePosition += shiftDir;
		neighbour->RelativePosition -= shiftDir;

		cell->CalculatePositionFromRelativePos();
		neighbour->CalculatePositionFromRelativePos();

		cell->AnimatePosition(0.25);

		return true;
	}
	return false;
}

bool Grid::WinCondition() {
	for (int x = 0; x < Helpers::GRID_SIZE; x++)
	{
		for (int y = 0; y < Helpers::GRID_SIZE; y++)
		{
			Cell* cell = GetCell(x, y);
			if (cell->Value == 2048) {
				return true;
			}
		}
	}
	return false;
}

bool Grid::IsAvailableMoveToward(Vector2i dir) {
	for (int x = 0; x < Helpers::GRID_SIZE; x++)
	{
		for (int y = 0; y < Helpers::GRID_SIZE; y++)
		{
			Cell* cell = GetCell(x, y);
			if (cell->Value == 0) continue;

			int xOffset = x + dir.x;
			int yOffset = y + dir.y;
			if (xOffset < 0 || xOffset >= Helpers::GRID_SIZE) continue;
			if (yOffset < 0 || yOffset >= Helpers::GRID_SIZE) continue;

			Cell* neighbour = GetCell(xOffset, yOffset);
			if (neighbour->Value == 0 || neighbour->Value == cell->Value)
				return true;
		}
	}
	return false;
}

bool Grid::LooseCondition() {
	return !IsAvailableMoveToward(Vector2i::up())
		&& !IsAvailableMoveToward(Vector2i::down())
		&& !IsAvailableMoveToward(Vector2i::left())
		&& !IsAvailableMoveToward(Vector2i::right());
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

void Grid::Update(float dT) {
	for (int x = 0; x < Helpers::GRID_SIZE; x++)
	{
		for (int y = 0; y < Helpers::GRID_SIZE; y++)
		{
			Cell* cell = GetCell(x, y);
			cell->Update(dT);
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