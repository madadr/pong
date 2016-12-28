#include "GameWindow.hpp"

GameWindow::GameWindow(int w, int h)
	: width(w),
	height(h),
	margin(20),
	window(nullptr),
	renderer(nullptr),
	racket1(nullptr),
	racket2(nullptr),
	ball(nullptr),
	quit(false),
	scoreboard(nullptr)
{
	init();

	scoreboard = new Scoreboard(renderer, width / 2, 40);

	int racket_width = width/25;
	int racket_height = height/5;
	int racket1_x = margin - 1;
	int racket2_x = width - racket_width - margin + 1;
	int racket_y = height/2;
	racket1 = new Racket(window, renderer, racket1_x, racket_y, racket_width, racket_height);
	racket2 = new Racket(window, renderer, racket2_x, racket_y, racket_width, racket_height);

	int ball_size = 10;
	int ball_x = width/2;
	int ball_y = height/2;
	ball = new Ball(window, renderer, ball_x, ball_y, ball_size);
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
	/*

	SDL_Rect gray1{ 0, 0, margin + racket1->w, height };
	SDL_Rect gray2{ width - margin - racket1->w, 0, margin + racket1->w, height };

	SDL_SetRenderDrawColor(renderer, 10, 10, 10, 0xFF);
	SDL_RenderFillRect(renderer, &gray1);
	SDL_RenderFillRect(renderer, &gray2);*/
}

void GameWindow::play()
{
	while (!quit)
	{
		event_handler();
		move_ball();
		render_objects();
		delay();
	}
}

void GameWindow::render_objects()
{
	//Clear screen
	SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0xFF );
	SDL_RenderClear( renderer );

	// render playground
	render_background();
	
	// Render objects
	ball->render();
	racket1->render();
	racket2->render();

	// render scoreboard
	scoreboard->render();

	//Update screen
	SDL_RenderPresent( renderer );
}

void GameWindow::event_handler()
{
	while(SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
			quit = true;
		else if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_a:
				racket1->up();
				break;
			case SDLK_z:
				racket1->down();
				break;
			case SDLK_UP:
				racket2->up();
				break;
			case SDLK_DOWN:
				racket2->down();
				break;
			default:
				break;
			}
//			render_objects();
		}
	}
}

void GameWindow::delay() const
{
	std::this_thread::sleep_for(std::chrono::milliseconds(7));
}

void GameWindow::move_ball()
{
	// collision with wall
	if (ball->y <= 0 || (ball->y + ball->h) >= height)
	{
		ball->dy *= -1.;
	}

	int rbm_width = racket2->w + ball->w + margin; // racket, ball and margin width
	if(ball->dx > 0)
	{
		if(ball->x < width - rbm_width - 1)
		{	
			ball->move();
		}
		else if(ball->x >= width - rbm_width - 1)
		{	
			// collision with racket
			if(ball->y + ball->h >= racket2->y && ball->y <= racket2->y + racket2->h)
			{	
				// ball->dy = -(ball->dx/20) * (racket2->x - ball->x);
				ball->dy = -(ball->dx/random_number(40)) * (racket2->y + racket2->h/2 - ball->y - ball->h / 2);
				ball->dx *= -1.;
			}
			else	// racket didn't "bounce" ball
			{
				while(ball->x < width + ball->w)
				{	
					ball->move();
					render_objects();
					delay();
					event_handler();	// avoids rackets freeze (when action)
				}
				++(*scoreboard)[0];
				scoreboard->update1();
				ball->reset();
			}
		}
	}
	else if(ball->dx < 0)
	{
		if(ball->x > rbm_width - ball->w)
		{			
			ball->move();
		}
		else if(ball->x <= rbm_width - ball->w)
		{	
			// collision with racket
			if(ball->y + ball->h >= racket1->rect.y && ball->y <= racket1->rect.y + racket1->rect.h)
			{	
				ball->dy = -(ball->dx / random_number(40)) * (racket1->y + racket1->h / 2 - ball->y - ball->h/2);
				// ball->dy = -(ball->dx/20) * (racket1->x + ball->x);
				ball->dx *= -1;
			}
			else // racket didn't "bounce" ball
			{
				while(ball->x >= -ball->w)
				{	
					ball->move();
					render_objects();
					delay();
					event_handler();	// avoids rackets freeze (when action)
				}
				++(*scoreboard)[1];
				scoreboard->update2();
				ball->reset();
			}
		}
	}
}

int GameWindow::random_number(const int& number) const
{
	std::random_device rd;
	std::uniform_int_distribution<int> dist(number - 15, number + 30);
	return std::move(dist(rd));
}

