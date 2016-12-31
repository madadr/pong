#ifndef TEXT_HPP___
#define TEXT_HPP___

#ifdef _WIN32
#include <SDL.h>
#include <SDL_ttf.h>
#endif
#ifdef _WIN64
#include <SDL.h>
#include <SDL_ttf.h>
#endif
#ifdef __unix__
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#endif

#include <iostream>
#include <string>
#include "GameWindow.hpp"

class Text
{
private:
	std::string text;
	int x;
	int y;
	SDL_Rect rect;
	SDL_Texture* texture;
	TTF_Font* font;
	GameWindow* game_window;
public:
	Text(GameWindow* gw, std::string text, const int& x, const int& y, const int& font_size);
	~Text();
	Text(const Text&) = delete;
	Text(Text&&) = delete;
	Text& operator=(const Text&) = delete;
	Text& operator=(Text&&) = delete;
	void render() const;
private:
	void move_left_side_text();
	void init();
};


#endif
