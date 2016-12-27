#ifndef BALL_H___
#define BALL_H___

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

class Ball
{
    friend class GameWindow;
private:
    SDL_Rect rect;
    SDL_Window* window_ptr;
    SDL_Renderer* renderer_ptr;
    const int init_x;
    const int init_y;
    int& x;
    int& y;
    int& w;
    int& h;
    double dx;
    double dy;
public:
    explicit Ball(SDL_Window* window, SDL_Renderer* renderer, int x, int y, int size);
    ~Ball() = default;
	Ball(const Ball&) = delete;
	Ball(Ball&&) = delete;
	Ball& operator=(const Ball&) = delete;
	Ball& operator=(Ball&&) = delete;
    // object control methods
	void render();
    void reset();
};

#endif