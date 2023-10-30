#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Helpers.h"

using namespace std;

struct WindowData {
	const char* title;
	int xpos;
	int ypos;
	int width;
	int height;
	bool fullscreen;
};

class Clock {
public:
	Clock();
	~Clock();

	void Tick();
	double DeltaTime() { return deltaTime; }
	int FPS() { return fps; }

private:
	int fps;
	double deltaTime;
	Uint64 currentPerformance;
	Uint64 lastPerformance;
};

class App {

public:
	Clock clock;

	App();
	~App();

	void Init(WindowData data);

	void HandleEvents();
	void Update();
	void Render();
	void Clean();
	
	bool IsRunning() { return running; }

private:
	bool running;
	SDL_Window* window;
	SDL_Renderer* renderer;
};