#pragma once

#include "Helpers.h"
#include "SDL.h"

class GameObject {
protected:
	Vector2 position;
	Vector2 size;
	Vector2 anchors;
public:
	Vector2 WorldPosition;

	GameObject(Vector2 _position, Vector2 _size);
	GameObject(Vector2 _position);
	GameObject();
	~GameObject();

	Vector2 Position() { return position; }
	Vector2 Size() { return size; }
	Vector2 Anchors() { return anchors; }
	SDL_Rect* GetWorldRect();

	void SetPosition(Vector2 _position);
	void SetSize(Vector2 _size);
	void SetAnchors(Vector2 _anchors);
	void CalculateWorldPosition();

	virtual void Update(float dT);
	virtual void Render(SDL_Renderer* renderer);
};