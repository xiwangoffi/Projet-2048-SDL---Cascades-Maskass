#include "Cell.h"

Cell::Cell(Vector2i _position, int value) : GameObject(Vector2::zero(), Vector2::one()* Helpers::TILE_PSIZE), RelativePosition(_position), Value(value), hasMerged(false)
{
	Vector2 pos(
		RelativePosition.y * Helpers::TILE_PSIZE + (RelativePosition.y + 3) * Helpers::TILE_PMARGIN + Helpers::TILE_PMARGIN,
		RelativePosition.x * Helpers::TILE_PSIZE + (RelativePosition.x + 3) * Helpers::TILE_PMARGIN + Helpers::TILE_PMARGIN
	);
	pos -= Vector2::one() * Helpers::MAP_PSIZE * 0.5f;
	SetPosition(pos);
}

Cell::~Cell()
{}

void Cell::Update(float dT)
{}

void Cell::Render(SDL_Renderer* renderer) {
	if (Value <= 0) return;

	SDL_Rect rect = {
		WorldPosition.x,
		WorldPosition.y,
		size.x,
		size.y
	};

	SDL_RenderCopy(renderer, Textures::TileTextures[Value], NULL, &rect);
}

bool Cell::operator+(Cell& cellToMerge)
{
	if (Value != cellToMerge.Value) return false;
	if (hasMerged || cellToMerge.hasMerged) return false;

	Value *= 2;
	cellToMerge.Value = 0;
	return true;
}