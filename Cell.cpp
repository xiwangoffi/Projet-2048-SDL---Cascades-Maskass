#include "Cell.h"

Cell::Cell(Vector2 position, int value) : GameObject(position, Vector2(200, 200)), Value(value), hasMerged(false)
{}

Cell::~Cell()
{}

void Cell::Update(float dT) {
}

void Cell::Render(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, Textures::TileTextures[Value], NULL, GetWorldRect());
}

bool Cell::operator+(Cell& cellToMerge)
{
	if (Value != cellToMerge.Value) return false;
	if (hasMerged || cellToMerge.hasMerged) return false;

	Value *= 2;
	cellToMerge.Value = 0;
	return true;
}