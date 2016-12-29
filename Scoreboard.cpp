#include "Scoreboard.hpp"

Scoreboard::Scoreboard(SDL_Renderer* renderer, const int& x, const int& y)
	: renderer_ptr(renderer),
	  x1(x - 120), x2(x + 100), // TODO: make x1, x2 dependent of GameWindow object
	  y1(y), y2(y),
	  score1(0), score2(0),
	  font(nullptr)
{
	if (TTF_Init() == -1)
	{
		std::cerr << "Cannot init TTF renderer. " << TTF_GetError() << std::endl;
		exit(EXIT_FAILURE); // TODO: Throw exception
	}

	font = TTF_OpenFont("font.ttf", 50);
	if (font == nullptr)
	{
		std::cerr << "Font not found." << std::endl;
		exit(EXIT_FAILURE); // TODO: Throw exception
	}
	update1();
	update2();
}

Scoreboard::~Scoreboard()
{
	SDL_DestroyTexture(text1_texture);
	SDL_DestroyTexture(text2_texture);
	TTF_Quit();
}

void Scoreboard::update1()
{
	update(score1, x1, y1, &text1_rect, &text1_texture);
}


void Scoreboard::update2()
{
	update(score2, x2, y2, &text2_rect, &text2_texture);
}

void Scoreboard::render()
{
	SDL_SetRenderDrawColor(renderer_ptr, 0xFF, 0x00, 0xFF, 0xFF);
	SDL_RenderCopy(renderer_ptr, text1_texture, nullptr, &text1_rect);
	SDL_RenderCopy(renderer_ptr, text2_texture, nullptr, &text2_rect);
	//	SDL_RenderPresent(renderer_ptr);
}

int& Scoreboard::operator[](const int& index)
{
	if (index == 0)
		return score1;
	else if (index == 1)
		return score2;
	else
	{
		throw std::exception("Wrong index");
	}
}

void Scoreboard::update(const int& score, const int& x, const int& y, SDL_Rect* text_rect, SDL_Texture** text_texture)
{
	// destroy old texture
	SDL_DestroyTexture(*text_texture);
	text_texture = nullptr;

	int text_width;
	int text_height;
	SDL_Surface* surface;
	SDL_Color textColor = {255, 255, 255, 0};

	surface = TTF_RenderText_Solid(font, std::to_string(score).c_str(), textColor);
	*text_texture = SDL_CreateTextureFromSurface(renderer_ptr, surface);
	text_width = surface->w;
	text_height = surface->h;
	SDL_FreeSurface(surface);
	text_rect->x = x;
	text_rect->y = y;
	text_rect->w = text_width;
	text_rect->h = text_height;
}
