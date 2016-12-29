#include "GameWindow.hpp"

GameWindow::GameWindow(const int& w, const int& h, const int& speed)
	: width(w),
	  height(h),
	  margin(20),
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

	scoreboard = new Scoreboard(renderer, width / 2, 40);

	int racket_width = width / 25;
	int racket_height = height / 5;
	int racket1_x = margin - 1;
	int racket2_x = width - racket_width - margin + 1;
	int racket_y = height / 2;
	racket1 = new Racket(this, racket1_x, racket_y, racket_width, racket_height, SDL_SCANCODE_A, SDL_SCANCODE_Z);
	racket2 = new Racket(this, racket2_x, racket_y, racket_width, racket_height, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN);

	int ball_size = 10;
	int ball_x = width / 2;
	int ball_y = height / 2;
	ball = new Ball(this, ball_x, ball_y, ball_size);
}

GameWindow::~GameWindow()
{
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
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
			std::cerr << "Warning: Linear texture filtering not enabled!" << std::endl;

		//Create window
		window = SDL_CreateWindow("Ping pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
		if (window == nullptr)
		{
			std::cerr << "Cannot create SDL window. " << SDL_GetError() << std::endl;
			exit(EXIT_FAILURE); // TODO: Throw exception
		}
		else
		{
			//Create renderer for window
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
			if (renderer == nullptr)
			{
				std::cerr << "Cannot init SDL renderer. " << std::endl;
				exit(EXIT_FAILURE); // TODO: Throw exception
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
			}
		}
	}
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

	/*while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
			game_running = false;
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_a)
				racket1->up();
			if (event.key.keysym.sym == SDLK_z)
				racket1->down();

			if (event.key.keysym.sym == SDLK_UP)
				racket2->up();
			if (event.key.keysym.sym == SDLK_DOWN)
				racket2->down();
		}
	}*/
}

void GameWindow::delay(const int& ms) const
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
