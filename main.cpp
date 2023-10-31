#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "App.h"
#include "Helpers.h"

int main(int argc, char* argv[]) {
	App* app = new App();

	WindowData data = {
		"Pirate Bay 2048",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		1280, 720, false
	};

	app->Init(data);
	while (app->IsRunning()) {
		app->HandleEvents();
		app->Update();
		app->Render();
	}

	app->Clean();
	return 0;
}