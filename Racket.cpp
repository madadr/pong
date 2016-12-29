#include "Racket.hpp"


Racket::Racket(GameWindow* gw, const int& x, const int& y, const int& width, const int& height, const SDL_Scancode& up, const SDL_Scancode& down)
	: game_window(gw),
	  rect({x, y, width, height}),
	  x(rect.x), y(rect.y),
	  w(rect.w), h(rect.h),
	  key_up(up), key_down(down)
{
}

void Racket::up()
{
	int step = 2;
	y -= step;
	if (y < 0)
		y = 0;
}

void Racket::down()
{
	int window_height;
	SDL_GetWindowSize(game_window->window, nullptr, &window_height);
	int step = 2;
	y += step;
	if (y > window_height - h)
		y = window_height - h;
}

void Racket::render()
{
	SDL_SetRenderDrawColor(game_window->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderFillRect(game_window->renderer, &rect);
}

void Racket::control(const Uint8* key_state)
{
	if (!key_state[key_up] != !key_state[key_down])
	{
		if (key_state[key_up])
			up();
		else if (key_state[key_down])
			down();
	}
}
