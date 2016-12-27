#include "GameWindow.hpp"

GameWindow::GameWindow(int w, int h)
	: width(w),
	height(h),
	window(nullptr),
	renderer(nullptr),
	racket1(nullptr),
	racket2(nullptr)
{
	init();
	int margin = 20;
	int racket_width = width/25;
	int racket_height = height/5;
	int racket1_x = width - racket_width - margin + 1;
	int racket2_x = margin - 1;
	int racket_y = height/2;
	racket1 = new Racket(window, renderer, racket1_x, racket_y, racket_width, racket_height);
	racket2 = new Racket(window, renderer, racket2_x, racket_y, racket_width, racket_height);
}

GameWindow::~GameWindow()
{
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}

void GameWindow::init()
{
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		std::cerr << "Cannot init SDL renderer. " << std::endl;
		exit(EXIT_FAILURE); // TODO: Throw exception
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
			std::cerr << "Warning: Linear texture filtering not enabled!" << std::endl;

		//Create window
		window = SDL_CreateWindow( "Ping pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN );
		if( window == nullptr )
		{
			std::cerr << "Cannot create SDL window. " << SDL_GetError() << std::endl;
			exit(EXIT_FAILURE); // TODO: Throw exception
		}
		else
		{
			//Create renderer for window
			renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_SOFTWARE );
			if (renderer == nullptr)
			{
				std::cerr << "Cannot init SDL renderer. " << std::endl;
				exit(EXIT_FAILURE); // TODO: Throw exception
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0xFF );
			}
		}
	}
}

void GameWindow::play()
{
	bool quit = false;
	while (!quit)
	{
		while(SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
				quit = true;
			else if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_UP:
					racket1->up();
					racket2->up();
					break;
				case SDLK_DOWN:
					racket1->down();
					racket2->down();
					break;
				default:
					break;
				}
			}
			//Clear screen
			SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0xFF );
			SDL_RenderClear( renderer );

			racket1->render();
			racket2->render();

			//Update screen
			SDL_RenderPresent( renderer );
		}
	}
}
