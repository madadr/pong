#ifndef GAMEINDOW_H____
#define GAMEINDOW_H____

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
#include "Racket.hpp"
#include "Ball.hpp"

class Racket;
class Ball;

class GameWindow
{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	int width;
	int height;
	int margin;
	bool quit;
	SDL_Event event;
	Racket* racket1;
	Racket* racket2;
	Ball* ball;
	void init();
public:
	explicit GameWindow(int w, int h);
	~GameWindow();
	GameWindow(const GameWindow&) = delete;
	GameWindow(GameWindow&&) = delete;
	GameWindow& operator=(const GameWindow&) = delete;
	GameWindow& operator=(GameWindow&&) = delete;
	friend class RectObject;

	void play();
private:
	void render_objects();
	void event_handler();
	void delay(int ms);
	void move_ball();
};

#endif
