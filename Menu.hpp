#ifndef MENU_HPP___
#define MENU_HPP___

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
#include <utility>
#include <array>
#include <memory>
#include "GameWindow.hpp"
#include "Text.hpp"

class Menu
{
public:
	enum text_place
	{
		LEFT1, RIGHT1,
		LEFT2, RIGHT2,
		LEFT3, RIGHT3,
		LEFT4, RIGHT4
	};
	using posXY = std::pair<int, int>;
	const std::array<posXY, 8> position;
	using sPtrText = std::shared_ptr<class Text>;
private:
	GameWindow* game_window;
	int font_size;

	sPtrText start, start_key;
	sPtrText info, info_key;
	sPtrText player1_up, player1_down;
	sPtrText player2_up, player2_down;
	sPtrText back, back_key;

	void init_startup_strings();
	void init_info_strings();
public:
	Menu(GameWindow* gw);
	~Menu() = default;
	Menu(const Menu&) = delete;
	Menu(Menu&&) = delete;
	Menu& operator=(const Menu&) = delete;
	Menu& operator=(Menu&&) = delete;
	void render_startup();
	void render_info();
};


#endif