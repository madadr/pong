#include "Racket.hpp"


Racket::Racket(GameWindow* gw, const side& racket_side, const SDL_Scancode& up, const SDL_Scancode& down)
	: game_window(gw),
	  key_up(up), key_down(down),
	  x(rect.x),
	  y(rect.y),
	  w(rect.w),
	  h(rect.h),
	  step(gw->height/240),
	  racket_side(racket_side)
{
	reset();
}


void Racket::up()
{
	y -= step;
	if (y < 0)
		y = 0;
}

void Racket::down()
{
	y += step;
	if (y > game_window->height - h)
		y = game_window->height - h;
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

void Racket::reset()
{
	int racket_w = game_window->width / 25;
	int racket_h = game_window->height / 4;
	int racket_x = (racket_side == LEFT) ? game_window->margin - 1 : game_window->width - game_window->margin + 1 - racket_w;
	int racket_y = game_window->height / 2 - racket_h / 2;
	rect = {std::move(racket_x), std::move(racket_y), std::move(racket_w), std::move(racket_h)};
}
