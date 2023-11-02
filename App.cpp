#include "App.h"

const int GRID_SIZE = 4;
static Vector2 ORIGIN = Vector2::zero();

GameObject* square;
Cell* cell;

App::App(WindowData data)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		cout << "Subsystems couldn't be initialize:" << SDL_GetError() << endl;
		exit(1);
	}

	IMG_Init(IMG_INIT_PNG);

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
	int x, y;
	SDL_GetWindowSize(window, &x, &y);
	ORIGIN.x = x;
	ORIGIN.y = y;
	ORIGIN *= 0.5f;

	Uint32 rendererFlags = SDL_RENDERER_ACCELERATED | (data.vsync ? SDL_RENDERER_PRESENTVSYNC : 0);
	renderer = SDL_CreateRenderer(window, -1, rendererFlags);
	if (!renderer) {
		cout << "Error creating renderer: " << SDL_GetError() << endl;
		exit(1);
	}

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	grid = new Grid(GRID_SIZE);
	grid->Init();
	running = true;

	square = new GameObject(Vector2(0, 0), Vector2(400, 400));
	cell = new Cell(Vector2(0, 0), 2);
}

App::~App()
{
	// ZAË AZRAZRA£RZ£ZA
	delete cell;
	delete square;
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
		default:
			break;
		}
	}
}

void App::Update()
{
	clock.Tick();

	square->Update(clock.DeltaTime());
	cell->Update(clock.DeltaTime());
}

void App::Render()
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	Debug::DisplayFPS(renderer, clock.FPS());

	//SDL_Surface* board_s = SDL_CreateRGBSurface(0, 600, 600, 32, 0, 0, 0, SDL_ALPHA_OPAQUE);

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

	square->Render(renderer);
	cell->Render(renderer);

	SDL_RenderPresent(renderer);
}

#pragma region GameObject

GameObject::GameObject(Vector2 _position, Vector2 _size) : position(_position), size(_size), anchors(Vector2::one() * 0.5f), WorldPosition(Vector2::zero())
{
	CalculateWorldPosition();
}

GameObject::GameObject(Vector2 _position) : GameObject(_position, Vector2::one())
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
	WorldPosition = ORIGIN;
	WorldPosition.x -= size.x * anchors.x;
	WorldPosition.y -= size.y * anchors.y;
}

void GameObject::Update(float dT) {
}

void GameObject::Render(SDL_Renderer* renderer) {
	SDL_Rect squareRect = {
		square->WorldPosition.x,
		square->WorldPosition.y,
		square->Size().x,
		square->Size().y
	};

	SDL_RenderCopy(renderer, Textures::TileTextures[2], NULL, &squareRect);
}

#pragma endregion GameObject

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