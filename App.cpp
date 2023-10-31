#include "App.h"

TTF_Font* font;
SDL_Color color = { 0, 0, 0 };
SDL_Texture* fpsTex;
SDL_Surface* fpsSurf;

const int GRID_SIZE = 4;

App::App() : window(nullptr), renderer(nullptr), grid(nullptr), running(false)
{}

App::~App()
{}

void App::Init(WindowData data) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		cout << "Subsystems couldn't be initialize:" << SDL_GetError() << endl;
		Clean();
	}

	if (TTF_Init() != 0) {
		cout << "Failed initializing SDL TTF: " << TTF_GetError() << endl;
		Clean();
	}

	Uint32 flags = data.fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
	window = SDL_CreateWindow(data.title, data.xpos, data.ypos, data.width, data.height, flags);
	if (!window) {
		cout << "Error creating window: " << SDL_GetError() << endl;
		Clean();
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		cout << "Error creating renderer: " << SDL_GetError() << endl;
		Clean();
	}

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	grid = new Grid(GRID_SIZE);
	grid->Init();
	running = true;

	// TEMPORARY THIS IS ABSOLUTE PIECE OF SHIT, DO NOT KEEP IT THERE, IT HAS TO BE IN FUCKING RESOURCES LIKE WOMEN HAVE TO BE IN THE KITCHEN PERIMETER
	font = TTF_OpenFont("res/fonts/Roboto-Regular.ttf", 14);
}

void App::HandleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0) {
		switch (event.type) {
		case SDL_QUIT:
			running = false;
			break;
		default:
			break;
		}
	}
}

void App::Update()
{
	clock.Tick();
}

void App::Render()
{
	SDL_RenderClear(renderer);

	string fpsText = "Current FPS: " + to_string(clock.FPS());
	fpsSurf = TTF_RenderText_Solid(font, fpsText.c_str(), color);
	fpsTex = SDL_CreateTextureFromSurface(renderer, fpsSurf);
	SDL_FreeSurface(fpsSurf);
	SDL_Rect rect = { 0, 0, fpsSurf->w, fpsSurf->h };

	SDL_RenderCopy(renderer, fpsTex, NULL, &rect);

	SDL_RenderPresent(renderer);
}

void App::Clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	TTF_CloseFont(font);
	SDL_DestroyTexture(fpsTex);
	TTF_Quit();
	SDL_Quit();
	cout << "Application is closing..." << endl;
}

#pragma region Clock

Clock::Clock() {
	currentPerformance = SDL_GetPerformanceCounter();
	lastPerformance = 0;
	deltaTime = 0;
	fps = 0;
}

Clock::~Clock()
{}

void Clock::Tick() {
	lastPerformance = currentPerformance;
	currentPerformance = SDL_GetPerformanceCounter();
	
	double elapsed = (currentPerformance - lastPerformance) * 1000 / (double)SDL_GetPerformanceFrequency();
	deltaTime = elapsed * 0.001f; // In seconds
	fps = 1.0 / deltaTime;
	
	SDL_Delay(floor(5 - deltaTime));
}

#pragma endregion Clock