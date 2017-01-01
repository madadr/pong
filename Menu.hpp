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
	using uPtrText = std::unique_ptr<class Text>;
private:
	GameWindow* game_window;
	int font_size;

	uPtrText start, start_key;
	uPtrText info, info_key;
	uPtrText player1_up, player1_down;
	uPtrText player2_up, player2_down;
	uPtrText back, back_key;
	uPtrText pause, pause_key;
	uPtrText game, paused;
	uPtrText unpause, unpause_key;
	uPtrText back_to_menu, win1, win2;
	uPtrText restart, restart_key;

	void init_startup_strings();
	void init_info_strings();
	void init_paused_strings();
	void init_win_strings();
	void render_win() const;
public:
	explicit Menu(GameWindow* gw);
	~Menu() = default;
	Menu(const Menu&) = delete;
	Menu(Menu&&) = delete;
	Menu& operator=(const Menu&) = delete;
	Menu& operator=(Menu&&) = delete;
	void render_startup() const;
	void render_info() const;
	void render_pause() const;
	void render_win1() const;
	void render_win2() const;
};


#endif
