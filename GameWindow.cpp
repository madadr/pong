#include "GameWindow.hpp"

GameWindow::GameWindow(const int& window_width, const int& window_height, const int& speed)
	: width(window_width),
	  height(window_height),
	  margin(window_width / 30),
	  window(nullptr),
	  renderer(nullptr),
	  racket1(nullptr),
	  racket2(nullptr),
	  ball(nullptr),
	  game_running(false),
	  scoreboard(nullptr),
	  speed(speed)
{
	init();

	racket1 = new Racket(this, Racket::side::LEFT, SDL_SCANCODE_A, SDL_SCANCODE_Z);
	racket2 = new Racket(this, Racket::side::RIGHT, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN);

	int ball_size = width / 60;
	ball = new Ball(this, std::move(ball_size));

	scoreboard = new Scoreboard(this);
}

GameWindow::~GameWindow()
{
	delete scoreboard;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void GameWindow::init()
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "Cannot init SDL renderer. " << std::endl;
		exit(EXIT_FAILURE); // TODO: Throw exception
	}
	//Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		std::cerr << "Warning: Linear texture filtering not enabled!" << std::endl;

	//Create window
	window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		std::cerr << "Cannot create SDL window. " << SDL_GetError() << std::endl;
		exit(EXIT_FAILURE); // TODO: Throw exception
	}

	//Create renderer for window
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	if (renderer == nullptr)
	{
		std::cerr << "Cannot init SDL renderer. " << std::endl;
		exit(EXIT_FAILURE); // TODO: Throw exception
	}

	// load icon surface 
	SDL_Surface* icon = SDL_LoadBMP("pong.ico");
	if (icon == nullptr)
	{
		std::cerr << "Cannot load icon file. " << std::endl;
		exit(EXIT_FAILURE); // TODO: Throw exception
	}
	// set window icon
	SDL_SetWindowIcon(window, icon);

	//Initialize renderer color
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
}

void GameWindow::render_background()
{
	// line in the middle
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	for (int i = 0; i < height; i += 5)
		SDL_RenderDrawPoint(renderer, width / 2, i);

	SDL_SetRenderDrawColor(renderer, 80, 80, 80, 0xFF);
	for (int i = 0; i < height; i += 10)
	{
		SDL_RenderDrawPoint(renderer, margin + racket1->w, i);
		SDL_RenderDrawPoint(renderer, width - margin - racket1->w, i);
	}
}

void GameWindow::play()
{
	game_running = true;
	while (game_running)
	{
		event_handler();
		ball->change_position();
		render_objects();
		delay(speed);
	}
}

void GameWindow::render_objects()
{
	//Clear screen
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(renderer);

	// render playground
	render_background();

	// Render objects
	ball->render();
	racket1->render();
	racket2->render();

	// render scoreboard
	scoreboard->render();

	//Update screen
	SDL_RenderPresent(renderer);
}

void GameWindow::event_handler()
{
	const Uint8* key_state = SDL_GetKeyboardState(nullptr);
	SDL_PumpEvents();
	if (SDL_PollEvent(&event) != 0 && event.type == SDL_QUIT)
		game_running = false;

	racket1->control(key_state);
	racket2->control(key_state);
}

void GameWindow::delay(const int& ms) const
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
