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
#include "Racket.hpp"

class GameWindow
{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	int width;
	int height;
	SDL_Event event;
	Racket* racket1;
	Racket* racket2;
	void init();
	// void racket_up(SDL_Rect& racket);
	// void racket_down(SDL_Rect& racket);
	// void racket_render(SDL_Rect& racket);
public:
	GameWindow(int w, int h);
	~GameWindow();
	GameWindow(const GameWindow&) = delete;
	GameWindow(GameWindow&&) = delete;
	GameWindow& operator=(const GameWindow&) = delete;
	GameWindow& operator=(GameWindow&&) = delete;
	friend class RectObject;

	void play();
};

#endif
