#include "Racket.hpp"


Racket::Racket(SDL_Window* window, SDL_Renderer* renderer, int x, int y, int width, int height)
    : window_ptr(window),
    renderer_ptr(renderer),
	rect({x, y, width, height})
{
    
}

void Racket::up()
{
	int step = 20;
	if(rect.y - step >= 0)
		rect.y -= step;
}

void Racket::down()
{
	int window_height;
	SDL_GetWindowSize(window_ptr, nullptr, &window_height);
	int step = 20;
	if(rect.y + rect.h + step <= window_height)
		rect.y += step;
}

void Racket::render()
{
	SDL_SetRenderDrawColor( renderer_ptr, 0xFF, 0xFF, 0xFF, 0xFF );		
	SDL_RenderFillRect( renderer_ptr, &rect );
}