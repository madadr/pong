#include "Text.hpp"


Text::Text(GameWindow* gw, const std::string& text, const int& x, const int& y, const int& font_size)
	: game_window(gw),
	  text(text), x(x), y(y),
	  font(TTF_OpenFont("font.ttf", font_size))
{
	if (font == nullptr)
	{
		std::cerr << "Font not found." << std::endl;
		exit(EXIT_FAILURE); // TODO: Throw exception
	}

	init();
}

Text::~Text()
{
	TTF_CloseFont(font);
}

// NOTE: Rather "prepare to render". After calling render() on Text obj, you must call SDL_RenderPresent to display text.
void Text::render() const
{
	SDL_SetRenderDrawColor(game_window->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderCopy(game_window->renderer, texture, nullptr, &rect);
	// Call SDL_RenderPresent(game_window->renderer); to display !
}

void Text::move_left_side_text()
{
	SDL_Surface* surface;
	SDL_Color textColor = {0xFF, 0xFF, 0xFF, 0};
	surface = TTF_RenderText_Solid(font, text.c_str(), textColor);
	x -= surface->w;
	SDL_FreeSurface(surface);
	surface = nullptr;
}

void Text::init()
{
	SDL_Surface* surface;
	SDL_Color textColor = {0xFF, 0xFF, 0xFF, 0};

	surface = TTF_RenderText_Solid(font, text.c_str(), textColor);
	texture = SDL_CreateTextureFromSurface(game_window->renderer, surface);

	rect.x = x;
	rect.y = y;
	rect.w = surface->w;
	rect.h = surface->h;

	// check if text is on the left side from the game_window middle, if yes - it must be moved
	if (x < game_window->width / 2)
	{
		x -= rect.w;
		rect.x -= rect.w;
	}
	SDL_FreeSurface(surface);
	surface = nullptr;
}
