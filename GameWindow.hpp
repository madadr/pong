#ifndef GAMEWINDOW_HPP___
#define GAMEWINDOW_HPP___

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
#include <thread>
#include <chrono>
#include <random>
#include "Racket.hpp"
#include "Ball.hpp"
#include "Scoreboard.hpp"


class Ball;
class Racket;
class Scoreboard;

class GameWindow
{
public:
	friend class Ball;
	friend class Racket;
	friend class Scoreboard;
public:
private:
	int speed;
	SDL_Window* window;
	SDL_Renderer* renderer;
	int width;
	int height;
	int margin;
	bool game_running;
	SDL_Event event;
	Racket* racket1;
	Racket* racket2;
	Ball* ball;
	Scoreboard* scoreboard;
public:
	explicit GameWindow(const int& w, const int& h, const int& speed);
	~GameWindow();
	GameWindow(const GameWindow&) = delete;
	GameWindow(GameWindow&&) = delete;
	GameWindow& operator=(const GameWindow&) = delete;
	GameWindow& operator=(GameWindow&&) = delete;

	void play();
private:
	void init();
	void render_background();
	void render_objects();
	void event_handler();
	void delay(const int& ms) const;
	int random_number(const int& number) const;
};

#endif
