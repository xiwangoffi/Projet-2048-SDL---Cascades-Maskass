#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "App.h"
#include "Helpers.h"
#include "Resources.h"

int main(int argc, char* argv[]) {
	WindowData data = {
		"Pirate Bay 2048",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		1280, 720, false, false
	};

	App app(data);
	InitResources(app.GetRenderer());

	while (app.IsRunning()) {
		app.HandleEvents();
		app.Update();
		app.Render();
	}

	CleanResources();
	return 0;
}