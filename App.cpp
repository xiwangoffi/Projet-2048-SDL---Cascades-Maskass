#include "App.h"

App::App(WindowData data)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		cout << "Subsystems couldn't be initialize:" << SDL_GetError() << endl;
		exit(1);
	}

	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

	if (TTF_Init() != 0) {
		cout << "Failed initializing SDL TTF: " << TTF_GetError() << endl;
		exit(1);
	}

	Uint32 windowFlags = data.fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
	window = SDL_CreateWindow(data.title, data.xpos, data.ypos, data.width, data.height, windowFlags);
	if (!window) {
		cout << "Error creating window: " << SDL_GetError() << endl;
		exit(1);
	}

	// Set Origin point to the center of the window
	int x, y;
	SDL_GetWindowSize(window, &x, &y);
	Helpers::ORIGIN.x = x;
	Helpers::ORIGIN.y = y;
	Helpers::ORIGIN *= 0.5f;

	Uint32 rendererFlags = SDL_RENDERER_ACCELERATED | (data.vsync ? SDL_RENDERER_PRESENTVSYNC : 0);
	renderer = SDL_CreateRenderer(window, -1, rendererFlags);
	if (!renderer) {
		cout << "Error creating renderer: " << SDL_GetError() << endl;
		exit(1);
	}

	srand(time(nullptr));
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	grid = new Grid(Helpers::GRID_SIZE);
	grid->Init();
	running = true;
}

App::~App()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	TTF_Quit();
	SDL_Quit();
	cout << "Application is closing..." << endl;
}

void App::HandleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0) {
		switch (event.type) {
		case SDL_QUIT:
			running = false;
			break;
		case SDL_KEYDOWN:
			HandleKeyDown(event.key.keysym.sym);
		default:
			break;
		}
	}
}

void App::HandleKeyDown(int keysym) {
	switch (keysym) {
	case SDLK_UP:
		grid->ShiftTilesTowards(Vector2i(0, -1));
		break;
	case SDLK_DOWN:
		grid->ShiftTilesTowards(Vector2i(0, 1));
		break;
	case SDLK_RIGHT:
		grid->ShiftTilesTowards(Vector2i(1, 0));
		break;
	case SDLK_LEFT:
		grid->ShiftTilesTowards(Vector2i(-1, 0));
		break;
	default:
		break;
	}
}

void App::Update()
{
	clock.Tick();
}

void App::Render()
{
	SDL_SetRenderDrawColor(renderer, 113, 188, 225, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	Debug::DisplayFPS(renderer, clock.FPS());

	SDL_Rect mapRect = {
		Helpers::ORIGIN.x - Helpers::MAP_PSIZE * 0.5,
		Helpers::ORIGIN.y - Helpers::MAP_PSIZE * 0.5,
		Helpers::MAP_PSIZE, Helpers::MAP_PSIZE
	};

	SDL_RenderCopy(renderer, Textures::Map, NULL, &mapRect);

	Vector2 worldPos(Helpers::ORIGIN.x - Helpers::MAP_PSIZE * 0.5, Helpers::ORIGIN.y - Helpers::MAP_PSIZE * 0.5);

	SDL_Rect cellRect = {
		0, 0,
		Helpers::CELL_PSIZE,
		Helpers::CELL_PSIZE
	};

	for (int x = 0; x < Helpers::GRID_SIZE; x++)
	{
		for (int y = 0; y < Helpers::GRID_SIZE; y++) {
			int i = x * Helpers::GRID_SIZE + y;
			cellRect.x = x * Helpers::CELL_PSIZE + Helpers::CELL_PMARGIN + worldPos.x;
			cellRect.y = y * Helpers::CELL_PSIZE + Helpers::CELL_PMARGIN + worldPos.y;
			SDL_RenderCopy(renderer, Textures::Cell, NULL, &cellRect);
		}
	}

	grid->Render(renderer);

	//for (int i = 0; i < 4; i++)
	//{
	//	for (int j = 0; j < 4; j++) {
	//		int index = i * 4 + j;
	//		square[index].x = j * 145 + 20;
	//		square[index].y = i * 145 + 20;
	//		square[index].w = 125;
	//		square[index].h = 125;

	//	}
	//}

	//SDL_Rect board;
	//board.x = 1280 / 2 - 300;
	//board.y = 720 / 2 - 300;
	//board.w = board_s->w;
	//board.h = board_s->h;

	//SDL_Rect square[16];

	//for (int i = 0; i < 4; i++)
	//{
	//	for (int j = 0; j < 4; j++) {
	//		int index = i * 4 + j;
	//		square[index].x = j * 145 + 20;
	//		square[index].y = i * 145 + 20;
	//		square[index].w = 125;
	//		square[index].h = 125;
	//		SDL_FillRect(board_s, &square[index], SDL_MapRGB(board_s->format, 255, 0, 0));
	//	}
	//}

	//SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, board_s);

	//SDL_RenderCopy(renderer, texture, NULL, &board);

	SDL_RenderPresent(renderer);
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