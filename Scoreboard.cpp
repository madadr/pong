#include "Scoreboard.hpp"

Scoreboard::Scoreboard(GameWindow* gw)
	: game_window(gw),
	  score1(0), score2(0),
	  font(nullptr),
	  x1(game_window->width / 2 - game_window->width / 10),
	  x2(game_window->width / 2 + game_window->width / 10),
	  y1(game_window->height / 15),
	  y2(game_window->height / 15)

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
	move_text1();
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
	SDL_SetRenderDrawColor(game_window->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderCopy(game_window->renderer, text1_texture, nullptr, &text1_rect);
	SDL_RenderCopy(game_window->renderer, text2_texture, nullptr, &text2_rect);
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
	static int text_width;
	static int text_height;
	SDL_Surface* surface;
	static SDL_Color textColor = {255, 255, 255, 0};

	surface = TTF_RenderText_Solid(font, std::to_string(score).c_str(), textColor);
	*text_texture = SDL_CreateTextureFromSurface(game_window->renderer, surface);
	text_width = surface->w;
	text_height = surface->h;
	SDL_FreeSurface(surface);

	text_rect->x = x;
	text_rect->y = y;
	text_rect->w = text_width;
	text_rect->h = text_height;

	if (text_rect->x < game_window->width / 2)
	{
		if (score1 == 9)
			x1 -= surface->w;
		else if (score1 == 99)
			x1 -= surface->w / 2;
		else if (score1 == 999)
			x1 -= surface->w / 3;
	}
}

void Scoreboard::move_text1()
{
	// moves score1 text at the same distance from middle as score2 text
	static int text_width;
	static int text_height;
	SDL_Surface* surface;
	static SDL_Color textColor = {255, 255, 255, 0};

	surface = TTF_RenderText_Solid(font, std::to_string(0).c_str(), textColor);
	text1_texture = SDL_CreateTextureFromSurface(game_window->renderer, surface);
	text_width = surface->w;
	text_height = surface->h;

	x1 -= surface->w;

	SDL_FreeSurface(surface);
	surface = nullptr;
}
