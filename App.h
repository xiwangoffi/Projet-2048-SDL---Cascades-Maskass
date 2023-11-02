#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Grid.h"
#include "Helpers.h"
#include "Vector2.h"
#include "Debug.h"

using namespace std;

struct WindowData {
	const char* title;
	int xpos;
	int ypos;
	int width;
	int height;
	bool fullscreen = false;
	bool vsync = true;
};

class Clock {
private:
	int fps;
	double deltaTime;
	Uint64 currentPerformance;
	Uint64 lastPerformance;

public:
	Clock();
	~Clock();

	void Tick();
	double DeltaTime() { return deltaTime; }
	int FPS() { return fps; }
};

class GameObject {
private:
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

class App {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	Grid* grid;
	bool running;

public:
	Clock clock;

	App(WindowData data);
	~App();

	SDL_Renderer* GetRenderer() { return renderer; }

	void HandleEvents();
	void Update();
	void Render();
	
	bool IsRunning() { return running; }
};