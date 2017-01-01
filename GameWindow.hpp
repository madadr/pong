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
#include <memory>
#include <random>
#include "Racket.hpp"
#include "Ball.hpp"
#include "Scoreboard.hpp"
#include "Text.hpp"
#include "Menu.hpp"

class Ball;
class Racket;
class Scoreboard;
class Text;
class Menu;

class GameWindow
{
public:
	friend class Ball;
	friend class Racket;
	friend class Scoreboard;
	friend class Text;
	friend class Menu;
private:
	const int MAX_SCORE;
	int speed;
	SDL_Window* window;
	SDL_Renderer* renderer;
	int width, height, margin;
	bool game_running;
	SDL_Event event;
	std::unique_ptr<Racket> racket1, racket2;
	std::unique_ptr<Ball> ball;
	std::unique_ptr<Scoreboard> scoreboard;
	std::unique_ptr<Menu> menu;
public:
	GameWindow(const int& window_width, const int& window_height, const int& max_score);
	~GameWindow();
	GameWindow(const GameWindow&) = delete;
	GameWindow(GameWindow&&) = delete;
	GameWindow& operator=(const GameWindow&) = delete;
	GameWindow& operator=(GameWindow&&) = delete;

	void play();
private:
	void init();
	void render_background() const;
	void render_objects();
	void event_handler();
	void delay(const int& ms) const;
	void display_menu();
	void pause_handler();
	void detect_game_end();
	void game_end_handler();
};

#endif
