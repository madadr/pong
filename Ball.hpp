#ifndef BALL_HPP___
#define BALL_HPP___

#ifdef _WIN32
#include <SDL.h>
#endif
#ifdef _WIN64
#include <SDL.h>
#endif
#ifdef __unix__
#include <SDL2/SDL.h>
#endif

#include <iostream>

#include <cmath>
#include "GameWindow.hpp"

class GameWindow;

class Ball
{
private:
	SDL_Rect rect;
	GameWindow* game_window;
	const int init_x;
	const int init_y;
	int &x, &y, &w, &h;
	double dx, dy;
public:
	explicit Ball(GameWindow* gw, const int& size);
	~Ball() = default;
	Ball(const Ball&) = delete;
	Ball(Ball&&) = delete;
	Ball& operator=(const Ball&) = delete;
	Ball& operator=(Ball&&) = delete;
	// object control methods
	void make_move();
	void change_position();
	int random_number(const int& number) const;
	void detect_game_end();
	void render() const;
	void reset();
};

#endif
