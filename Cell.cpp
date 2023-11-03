#include "Cell.h"

Cell::Cell(Vector2i _position, int value) : GameObject(Vector2::zero(), Vector2::one()* Helpers::TILE_PSIZE), RelativePosition(_position), Value(value), hasMerged(false), animationTime(0), animationDuration(0), startPosition(Vector2::zero()), targetPosition(Vector2::zero()), startSize(Vector2::zero()), targetSize(Vector2::one()* Helpers::TILE_PSIZE)
{
	CalculatePositionFromRelativePos();
	startPosition = targetPosition;
	SetPosition(targetPosition);
}

Cell::~Cell()
{}

void Cell::Update(float dT)
{
	if (animationDuration > 0) {
		animationTime += dT;
		float t = SDL_clamp(animationTime / animationDuration, 0, 1);
		Vector2 animatedPos = Helpers::Lerp(startPosition, targetPosition, Easing::QuadOut(t));
		SetPosition(animatedPos);

		Vector2 animatedSize = Helpers::Lerp(startSize, targetSize, Easing::BounceOut(t));
		SetSize(animatedSize);
	}
}

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

void Cell::AnimatePosition(float duration) {
	animationTime = 0;
	animationDuration = duration;
	startPosition = position;
}

void Cell::AnimateSize(float duration, Vector2 startSize) {
	animationTime = 0;
	animationDuration = duration;
	startSize = startSize;
}

void Cell::SetRelativePosition(Vector2i _position) {
	RelativePosition = _position;
	CalculatePositionFromRelativePos();
}

void Cell::CalculatePositionFromRelativePos() {
	Vector2 pos(
		RelativePosition.x * Helpers::TILE_PSIZE + (RelativePosition.x + 3) * Helpers::TILE_PMARGIN + Helpers::TILE_PMARGIN,
		RelativePosition.y * Helpers::TILE_PSIZE + (RelativePosition.y + 3) * Helpers::TILE_PMARGIN + Helpers::TILE_PMARGIN
	);
	pos -= Vector2::one() * Helpers::MAP_PSIZE * 0.5f;
	startPosition = position;
	targetPosition = pos;
}

bool Cell::operator+(Cell& cellToMerge)
{
	if (Value != cellToMerge.Value) return false;
	if (hasMerged || cellToMerge.hasMerged) return false;

	Value *= 2;
	cellToMerge.Value = 0;
	return true;
}