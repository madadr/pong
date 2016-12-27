#ifndef RACKET_H___
#define RACKET_H___

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

class Racket
{
private:
    SDL_Rect rect;
    SDL_Window* window_ptr;
    SDL_Renderer* renderer_ptr;
public:
    explicit Racket(SDL_Window* window, SDL_Renderer* renderer, int x, int y, int width, int height);
    ~Racket() = default;
	Racket(const Racket&) = delete;
	Racket(Racket&&) = delete;
	Racket& operator=(const Racket&) = delete;
	Racket& operator=(Racket&&) = delete;
    // object control methods
	void up();
	void down();
	void render();
};

#endif