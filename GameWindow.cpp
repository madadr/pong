#include "GameWindow.hpp"

GameWindow::GameWindow(const int& window_width, const int& window_height, const int& max_score)
	: width(window_width),
	  height(window_height),
	  margin(window_width / 30),
	  window(nullptr),
	  renderer(nullptr),
	  racket1(nullptr),
	  racket2(nullptr),
	  ball(nullptr),
	  scoreboard(nullptr),
	  menu(nullptr),
	  game_running(false),
	  speed(1),
	  MAX_SCORE(max_score)
{
	init();

	racket1 = std::make_unique<Racket>(this, Racket::side::LEFT, SDL_SCANCODE_A, SDL_SCANCODE_Z);
	racket2 = std::make_unique<Racket>(this, Racket::side::RIGHT, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN);

	int ball_size = width / 60;
	ball = std::make_unique<Ball>(this, std::move(ball_size));

	scoreboard = std::make_unique<Scoreboard>(this);
	menu = std::make_unique<Menu>(this);
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
		throw Error("Cannot init SDL renderer. ");

	//Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) // just warning, no exception
		throw Error("Warning: Linear texture filtering not enabled");

	//Create window
	window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if (window == nullptr)
		throw Error("Cannot create SDL window. " + static_cast<std::string>(SDL_GetError()));

	//Create renderer for window
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	if (renderer == nullptr)
		throw Error("Cannot init SDL renderer.");

	// load icon surface 
	SDL_Surface* icon = SDL_LoadBMP("pong.ico");
	if (icon == nullptr)
		throw Error("Cannot load icon file.");

	// init TTF
	if (TTF_Init() == -1)
		throw Error("Cannot init TTF renderer. " + static_cast<std::string>(TTF_GetError()));

	// set window icon
	SDL_SetWindowIcon(window, icon);

	//Initialize renderer color
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
}

void GameWindow::render_background() const
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
	display_menu();
	while (game_running)
	{
		event_handler();
		ball->change_position();
		render_objects();
		detect_game_end();
		//		delay(speed);
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

	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p)
		pause_handler();

	racket1->control(key_state);
	racket2->control(key_state);
}

void GameWindow::delay(const int& ms) const
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void GameWindow::display_menu()
{
	bool quit_menu = false;
	bool quit_info = false;
	render_objects();
	menu->render_startup();
	while (!quit_menu)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				quit_menu = true;
				game_running = false;
			}
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_s)
			{
				quit_menu = true;
				game_running = true;
			}
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_i)
			{
				render_objects();
				menu->render_info();
				while (!quit_info)
				{
					while (SDL_PollEvent(&event) != 0)
					{
						if (event.type == SDL_QUIT)
						{
							quit_info = true;
							quit_menu = true;
							game_running = false;
						}
						else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_b)
						{
							render_objects();
							menu->render_startup();
							quit_info = true;
							break;
						}
					}
				}
				quit_info = false;
			}
		}
	}
}

void GameWindow::pause_handler()
{
	bool quit_pause = false;
	menu->render_pause();
	while (!quit_pause)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				quit_pause = true;
				game_running = false;
			}
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p)
			{
				render_objects();
				quit_pause = true;
			}
		}
	}
}

void GameWindow::detect_game_end()
{
	if ((*scoreboard)[0] == MAX_SCORE || (*scoreboard)[1] == MAX_SCORE)
	{
		if ((*scoreboard)[0] == MAX_SCORE)
			menu->render_win1();
		else
			menu->render_win2();

		game_end_handler();
		scoreboard->reset();
		scoreboard->update1();
		scoreboard->update2();
		racket1->reset();
		racket2->reset();
	}
}

void GameWindow::game_end_handler()
{
	bool quit_end = false;
	while (!quit_end)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				quit_end = true;
				game_running = false;
			}
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_b)
			{
				render_objects();
				display_menu();
				quit_end = true;
			}
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_r)
			{
				render_objects();
				quit_end = true;
			}
		}
	}
}
