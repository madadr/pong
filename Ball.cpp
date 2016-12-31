#include "Ball.hpp"


Ball::Ball(GameWindow* gw, const int& size)
	: game_window(gw),
	  dx(2.0), dy(0),
	  init_x((gw->width / 2) - size / 2),
	  init_y((gw->height / 2) - size / 2),
	  rect({init_x, init_y, size, size}),
	  x(rect.x), y(rect.y),
	  w(rect.w), h(rect.h)
{
	reset();
}

void Ball::make_move()
{
	if (dx >= 0)
		x += static_cast<int>(dx < 1 ? ceil(dx) : dx);
	else
		x += static_cast<int>(dx > -1 ? floor(dx) : dx);

	if (dy >= 0)
		y += static_cast<int>(dy < 1 ? ceil(dy) : dy);
	else
		y += static_cast<int>(dy > -1 ? floor(dy) : dy);
}

void Ball::reset()
{
	x = init_x;
	y = init_y;
	dy = 0;
}

void Ball::render() const
{
	SDL_SetRenderDrawColor(game_window->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderFillRect(game_window->renderer, &rect);
}

void Ball::change_position()
{
	// collision with wall
	if (y <= 0 || (y + h) >= game_window->height)
	{
		dy *= -1.;
	}

	int rbm_width = game_window->racket2->w + w + game_window->margin; // racket, ball and margin width
	if (dx > 0)
	{
		if (x < game_window->width - rbm_width - 1)
		{
			make_move();
		}
		else if (x >= game_window->width - rbm_width - 1)
		{
			// collision with racket
			if (y + h >= game_window->racket2->y && y <= game_window->racket2->y + game_window->racket2->h)
			{
				dy = -(dx / random_number(40)) * (game_window->racket2->y + game_window->racket2->h / 2 - y - h / 2);
				dx *= -1.;
			}
			else // racket didn't "bounce" ball
			{
				while (x < game_window->width + w)
				{
					make_move();
					game_window->render_objects();
					game_window->delay(game_window->speed);
					game_window->event_handler(); // avoids rackets freeze (when action)
				}
				++(*game_window->scoreboard)[0];
				game_window->scoreboard->update1();
				reset();
			}
		}
	}
	else if (dx < 0)
	{
		if (x > rbm_width - w)
		{
			make_move();
		}
		else if (x <= rbm_width - w)
		{
			// collision with racket
			if (y + h >= game_window->racket1->y && y <= game_window->racket1->y + game_window->racket1->h)
			{
				dy = -(dx / random_number(40)) * (game_window->racket1->y + game_window->racket1->h / 2 - y - h / 2);
				dx *= -1;
			}
			else // racket didn't "bounce" ball
			{
				while (x >= -w)
				{
					make_move();
					game_window->render_objects();
					game_window->delay(game_window->speed);
					game_window->event_handler(); // avoids rackets freeze (when action)
				}
				++(*game_window->scoreboard)[1];
				game_window->scoreboard->update2();
				reset();
			}
		}
	}
}

int Ball::random_number(const int& number) const
{
	static std::random_device rd;
	std::uniform_int_distribution<int> dist(number - 15, number + 30);
	return std::move(dist(rd));
}
