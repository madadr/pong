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
#include "Text.hpp"

// TODO: make Scoreboard consistent with Text / Menu

class Scoreboard
{
private:
	int x1, x2, y1, y2;
	int score1, score2;
	using uPtrText = std::shared_ptr<class Text>;
	uPtrText score1_string;
	uPtrText score2_string;
	GameWindow* game_window;
	int font_size;
public:
	Scoreboard(GameWindow* gw);
	~Scoreboard() = default;
	Scoreboard(const Scoreboard&) = delete;
	Scoreboard(Scoreboard&&) = delete;
	Scoreboard& operator=(const Scoreboard&) = delete;
	Scoreboard& operator=(Scoreboard&&) = delete;
	void reset();
	void update1();
	void update2();
	void render() const;
	int& operator[](const int& index);
};

#endif
