#ifndef SCOREBOARD_HPP___
#define SCOREBOARD_HPP___

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

// TODO: make Scoreboard consistent with Text / Menu

class Scoreboard
{
private:
	int score1, score2;
	SDL_Rect text1_rect, text2_rect;
	SDL_Texture* text1_texture;
	SDL_Texture* text2_texture;
	GameWindow* game_window;
	TTF_Font* font;
	int x1, x2, y1, y2;
	void update(const int& score, const int& x, const int& y, SDL_Rect* text_rect, SDL_Texture** text_texture);
	void move_text1();
public:
	Scoreboard(GameWindow* gw);
	~Scoreboard();
	Scoreboard(const Scoreboard&) = delete;
	Scoreboard(Scoreboard&&) = delete;
	Scoreboard& operator=(const Scoreboard&) = delete;
	Scoreboard& operator=(Scoreboard&&) = delete;
	void update1();
	void update2();
	void render();
	int& operator[](const int& index);
};

#endif
