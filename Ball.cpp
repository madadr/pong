#include "Ball.hpp"


Ball::Ball(SDL_Window* window, SDL_Renderer* renderer, int x, int y, int size)
    : window_ptr(window),
    renderer_ptr(renderer),
	rect({x, y, size, size}),
    dx(3.0), dy(0),
    init_x(x), init_y(y),
    x(rect.x), y(rect.y),
    w(rect.w), h(rect.h)
{
    
}

void Ball::move()
{
	if (dx>=0)
		x += static_cast<int>(dx < 1 ? ceil(dx) : dx);
	else
		x += static_cast<int>(dx > -1 ? floor(dx) : dx);

	if (dy >= 0)
		y += static_cast<int>(dy < 1 ? ceil(dy) : dy);
	else
		y += static_cast<int>(dy > -1 ? floor(dy) : dy);

//	y += dy < 1 ? ceil(dy) : dy;
}

void Ball::reset()
{
    x = init_x;
    y = init_y;
    dy = 0;
}

void Ball::render()
{
	SDL_SetRenderDrawColor( renderer_ptr, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderFillRect( renderer_ptr, &rect );
}
