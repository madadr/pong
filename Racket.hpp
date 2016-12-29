#ifndef RACKET_HPP___
#define RACKET_HPP___

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
#include "GameWindow.hpp"
#include "Ball.hpp"

class Ball;
class GameWindow;

class Racket
{
	friend class Ball;
	friend class GameWindow;
private:
	SDL_Scancode key_up;
	SDL_Scancode key_down;
	SDL_Rect rect;
	GameWindow* game_window;
	int& x;
	int& y;
	int& w;
	int& h;
public:
	explicit Racket(GameWindow* gw, const int& x, const int& y, const int& width, const int& height, const SDL_Scancode& up, const SDL_Scancode& down);
	~Racket() = default;
	Racket(const Racket&) = delete;
	Racket(Racket&&) = delete;
	Racket& operator=(const Racket&) = delete;
	Racket& operator=(Racket&&) = delete;
	// object control methods
	void up();
	void down();
	void render();
	void control(const Uint8* key_state);
};

#endif
