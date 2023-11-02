#include "GameObject.h"

GameObject::GameObject(Vector2 _position, Vector2 _size) : position(_position), size(_size), anchors(Vector2::one() * 0.5f), WorldPosition(Vector2::zero())
{
	CalculateWorldPosition();
}

GameObject::GameObject(Vector2 _position) : GameObject(_position, Vector2::one())
{}

GameObject::GameObject() : GameObject(Vector2::zero(), Vector2::one())
{}

GameObject::~GameObject()
{}

SDL_Rect* GameObject::GetWorldRect() {
	SDL_Rect out;
	out.x = WorldPosition.x;
	out.y = WorldPosition.y;
	out.w = size.x;
	out.h = size.y;
	return &out;
}

void GameObject::SetPosition(Vector2 _position) {
	position = _position;
	CalculateWorldPosition();
}
void GameObject::SetSize(Vector2 _size) {
	size = _size;
	CalculateWorldPosition();
}
void GameObject::SetAnchors(Vector2 _anchors) {
	anchors = _anchors;
	CalculateWorldPosition();
}

void GameObject::CalculateWorldPosition() {
	WorldPosition = Helpers::ORIGIN + position;
	WorldPosition.x -= size.x * anchors.x;
	WorldPosition.y -= size.y * anchors.y;
}

void GameObject::Update(float dT) {

}

void GameObject::Render(SDL_Renderer* renderer) {

}