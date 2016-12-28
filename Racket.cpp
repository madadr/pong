#include "Racket.hpp"


Racket::Racket(SDL_Window* window, SDL_Renderer* renderer, int x, int y, int width, int height)
    : window_ptr(window),
    renderer_ptr(renderer),
	rect({x, y, width, height}),
    x(rect.x), y(rect.y),
    w(rect.w), h(rect.h)
{
    
}

void Racket::up()
{
	int step = 60;
	y -= step;
	if (y < 0)
		y = 0;
}

void Racket::down()
{
	int window_height;
	SDL_GetWindowSize(window_ptr, nullptr, &window_height);
	int step = 60;
	y += step;
	if (y > window_height - h)
		y = window_height - h;
}

void Racket::render()
{
	SDL_SetRenderDrawColor( renderer_ptr, 0xFF, 0xFF, 0xFF, 0xFF );		
	SDL_RenderFillRect( renderer_ptr, &rect );
}